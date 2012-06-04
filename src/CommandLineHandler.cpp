#include "../include/CommandLineHandler.h"

positional_options_description CommandLineHandler::pd;
options_description CommandLineHandler::options("Valid Options");
variables_map CommandLineHandler::arguments;

CommandLineHandler::CommandLineHandler(int argc, char **argv)
{
   options.add_options()
        ("file"   , value<std::string>(), "The filename of the Brainfuck program to load (.b or .bf extension preferred")
        ("dialect", value<std::string>()->default_value("brainfuck"), "Selects a Brainfuck dialect (only one may be used).  See doc for the list.")
        ("doc"    , value<std::string>(), "Describes a given Brainfuck variety (or lists them if left blank).")
        ("help"   , "Shows this message.")
        ("about"  , "Info about the author.");
    pd.add("file", 1);

    store(parse_command_line(argc, argv, options), arguments);
    notify(arguments);

    initDialects();

}

AbstractBF* CommandLineHandler::getDialect() {
    std::string dialect = arguments["dialect"].as<std::string>();
    std::string filename = arguments["file"].as<std::string>();

    if (arguments.count("dialect")) {
        if (dialect == "brainfuck") return new Brainfuck(filename);
        else if (dialect == "brainfuck-x1") return new Brainfuck_X1(filename);
    }

    try {
        throw std::invalid_argument("The \"" + dialect + "\" dialect, if it really exists, is not supported!");
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return nullptr;
}

void CommandLineHandler::initDialects()
{
    dialects["brainfuck"   ] = "Brainfuck (default)";
    dialects["brainfuck-x1"] = "Extended Brainfuck Type I";
    dialects["brainfuck-x2"] = "Extended Brainfuck Type II (Not Implemented)";
    dialects["brainfuck-x3"] = "Extended Brainfuck Type III (Not Implemented)";
}

bool CommandLineHandler::isValid() const
{
    return arguments.count("file");
}

bool CommandLineHandler::doesDialectExist(const std::string& thedialect) const
{
    return dialects.find(thedialect) != dialects.end();
}

void CommandLineHandler::printHelp()
{
    std::cout << options << std::endl;
    exit(EXIT_SUCCESS);
}

void CommandLineHandler::printDialects()
{
    std::cout << "Dialect list not yet implemented." << std::endl;
    exit(EXIT_SUCCESS);
}

void CommandLineHandler::printAbout()
{
    std::cout << "Copyright 2012 Corundum Media Group\n";
    exit(EXIT_SUCCESS);
}

void CommandLineHandler::handleArguments()
{
    if (arguments.count("help") || arguments.size() < 1) {
        printHelp();
    }
    else if (arguments.count("dialect") || !doesDialectExist(arguments["dialect"].as<std::string>())) {
        printDialects();
    }
}
