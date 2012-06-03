#include "../../include/dialect/Brainfuck.h"

Brainfuck::Brainfuck(const std::string& newfilename)
{
    tape.reserve(30000);
    index = tape.data();
    std::fill(tape.begin(), tape.end(), 0);
    filename = newfilename;
    pattern = boost::regex("[^]><+.,[-]", boost::regex::basic);
    initInstructions();
}

void Brainfuck::initInstructions()
{
    instructions['>'] = [&, this] () {  //Move the pointer to the right
        ++index;
        if (index == (tape.data() + tape.size())) tape.push_back(0);
    };
    instructions['<'] = [&, this] () {  //Move the pointer to the lefyt
        --index;
        try {
            if (index < tape.data())
                throw std::runtime_error("Error in program \"" + filename + "\"!  Pointer has fallen below 0!");
        }
        catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    };
    instructions['+'] = [&, this] () {  //Increment the value at the pointer
        ++(*index);
    };
    instructions['-'] = [&, this] () {  //Decrement the value at the pointer
        --(*index);
    };
    instructions['.'] = [&, this] () {  //Output the ASCII character at the pointer
        std::cout << *index;
    };
    instructions[','] = [&, this] () {  //Get one character of input
        std::cin >> *index;
    };
    instructions['['] = [&, this] () {  //Begin a loop

        if (!*index) {  //If the value under the pointer is 0, go past the matching ]
            int64_t tempbrace = 0;

            while (true) {
                if (*currentinstruction == '[') ++tempbrace;
                else if (*currentinstruction == ']') --tempbrace;

                if (!tempbrace) return;
                else ++currentinstruction;
            }
        }
    };
    instructions[']'] = [&, this] () {  //End a loop

        if (*index) {  //If the value under the pointer isn't 0, go back to the matching [
            int64_t tempbrace = 0;

            while (true) {
                if (*currentinstruction == ']') ++tempbrace;
                else if (*currentinstruction == '[') --tempbrace;

                if (!tempbrace) return;
                else --currentinstruction;
            }
        }
    };
}

void Brainfuck::open()
{
    file.open(filename);

    try {
        if (!file.good()) throw std::runtime_error("Could not open file \"" + filename + "\"!  Does it really exist?");
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ostringstream temp;
    temp << file.rdbuf();
    file.close();

    program = boost::regex_replace(temp.str(), pattern, std::string(""));
    currentinstruction = program.data();

    checkLoops();
}

void Brainfuck::run()
{
    while (currentinstruction <= &program.back()) nextInstruction();
}

void Brainfuck::checkLoops()
{
    std::stack<char> tempbracestack;

    for (const char i : program) {
        if (i == '[')
            tempbracestack.push(i);
        else if (i == ']')
            tempbracestack.pop();
    }

    try {
        if (!tempbracestack.empty())
            throw std::runtime_error("Program \"" + filename + "\" does not balance braces ([]) correctly!");
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Brainfuck::nextInstruction()
{
    try {
        instructions.at(*currentinstruction)();
    }
    catch (std::out_of_range&) {
    }
    currentinstruction++;
}
