#include <iostream>



#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

#include "./include/Declarations.h"
#include "include/CommandLineHandler.h"

using namespace boost::program_options;

int main(int argc, char **argv)
{
    CommandLineHandler CommandLine(argc, argv);
    std::unique_ptr<AbstractBF> program;

    if (CommandLine.isValid()) {
        program.reset(CommandLine.getDialect());
        program->open();
        program->run();
    }
    else
        CommandLine.printHelp();

    return EXIT_SUCCESS;
}
