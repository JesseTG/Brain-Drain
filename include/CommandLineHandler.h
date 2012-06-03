#ifndef COMMANDLINEHANDLER_H
#define COMMANDLINEHANDLER_H

#include "Declarations.h"
#include "./dialect/Brainfuck.h"
#include "./dialect/Brainfuck_X1.h"


#include <boost/program_options.hpp>

using namespace boost::program_options;

class CommandLineHandler
{
    public:
        CommandLineHandler(int argc, char **argv);
        ~CommandLineHandler() {}

        bool isValid();
        void printHelp();

        AbstractBF* getDialect();

    private:
        void initDialects();
        void handleArguments();

        static options_description options;
        static options_description dialects;
        static variables_map arguments;
        static positional_options_description pd;

};

#endif // COMMANDLINEHANDLER_H
