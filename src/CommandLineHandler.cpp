#include "../include/CommandLineHandler.h"

positional_options_description CommandLineHandler::pd;
options_description CommandLineHandler::dialects("Available Brainfuck Dialects");
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

    if (arguments.count("dialect") && arguments["dialect"].as<std::string>() == "brainfuck")
        return new Brainfuck(arguments["file"].as<std::string>());

    return nullptr;
    //TODO: Load if a filename was specified, show docs if not
}

void CommandLineHandler::initDialects()
{
    dialects.add_options()
        ("brainfuck"  , "Brainfuck (default)")
        ("brainfuck-x1", "Extended Brainfuck Type I")
        ("brainfuck-x2", "Extended Brainfuck Type II");
}

bool CommandLineHandler::isValid()
{
    return arguments.count("file");
}

void CommandLineHandler::printHelp()
{
    std::cout << options << std::endl;
    exit(EXIT_SUCCESS);
}

void CommandLineHandler::handleArguments()
{
    if (arguments.count("help") || arguments.size() < 1) {
        printHelp();
    }
    else if (arguments.count("dialect")) {
        std::cout << dialects << std::endl;
        exit(EXIT_SUCCESS);
    }
}
