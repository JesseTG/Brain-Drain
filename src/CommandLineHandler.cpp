#include "../include/CommandLineHandler.h"

options_description CommandLineHandler::options("Valid Options");
variables_map CommandLineHandler::arguments;

CommandLineHandler::CommandLineHandler(int argc, char **argv)
{
   options.add_options()
        ("file"   , value<std::string>(), "Load a Brainfuck program (.b or .bf extensions preferred).")
        ("dialect", value<std::string>(), "Selects a Brainfuck dialect (only one may be used).  See doc for the list.")
        ("doc"    , value<std::string>(), "Describes a given Brainfuck variety (or lists them if left blank).")
        ("help"   , "Shows this message.")
        ("about"  , "Info about the author.");
    store(parse_command_line(argc, argv, options), arguments);
    notify(arguments);

    if (arguments.count("help") || arguments.empty()) {
        std::cout << options << std::endl;
        exit(0);
    }
}

CommandLineHandler::~CommandLineHandler()
{
    //dtor
}
