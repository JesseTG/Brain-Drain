#include <iostream>



#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

#include "./include/Brainfuck.h"
using namespace boost::program_options;

int main(int argc, char **argv)
{
   options_description options("Valid Options");
   options.add_options()
        ("file" , value<std::string>(), "Load a Brainfuck program (.b or .bf extensions preferred).")
        ("brainfuck", "Explicitly enables \"vanilla\" Brainfuck (not required).")
        ("x"    , "Enables Extended Brainfuck Type I.")
        ("x2"   , "Enables Extended Brainfuck Types I and II.")
        ("x3"   , "Enables Extended Brainfuck Types I, II, and III.")
        ("help" , "Shows this message.")
        ("doc"  , value<std::string>(), "Describes a given Brainfuck variety (or lists them if left blank).")
        ("about", "Info about the author.");
    variables_map vm;
    store (parse_command_line(argc, argv, options), vm);

    if (vm.count("help") || vm.empty()) {
        std::cout << options << "\n";
        return 0;
    }
}
