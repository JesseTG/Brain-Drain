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

        bool isValid() const;

        void printHelp();

        AbstractBF* getDialect();

    private:
        bool doesDialectExist(const std::string& thedialect) const;
        void initDialects();
        void handleArguments();
        void printDialects();
        void printAbout();

        static boost::program_options::options_description            options;
        static std::unordered_map<std::string, std::string>           dialects;
        static boost::program_options::                               variables_map arguments;
        static boost::program_options::positional_options_description pd;

};

#endif // COMMANDLINEHANDLER_H
