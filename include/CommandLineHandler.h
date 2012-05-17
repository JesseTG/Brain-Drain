#ifndef COMMANDLINEHANDLER_H
#define COMMANDLINEHANDLER_H

#include <boost/program_options.hpp>

using namespace boost::program_options;

class CommandLineHandler
{
    public:
        CommandLineHandler(int argc, char **argv);
        ~CommandLineHandler();

        AbstractBF*

    private:
        static options_description options;
        static variables_map arguments;

};

#endif // COMMANDLINEHANDLER_H
