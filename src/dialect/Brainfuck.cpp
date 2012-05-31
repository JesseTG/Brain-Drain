#include "../../include/dialect/Brainfuck.h"

Brainfuck::Brainfuck(const std::string& newfilename)
{
    tape.reserve(30000);
    index = tape.data();
    std::fill(tape.begin(), tape.end(), 0);
    filename = newfilename;
    pattern = boost::regex("[^]><+.,[@$!}{~^&|-]", boost::regex::basic);

    instructions['>'] = [&, this] () {
        if (index == (tape.data() + tape.size())) tape.push_back(0);
        ++index;
    };
    instructions['<'] = [&, this] () {
        --index;
        if (index < tape.data()) throw std::runtime_error("Error in program \"" + filename + "\"!  Pointer has fallen below 0!");
    };
    instructions['+'] = [&, this] () {
        ++*index;
    };
    instructions['-'] = [&, this] () {
        --*index;
    };
    instructions['.'] = [&, this] () {
        std::cout << "Output\n";
        std::cout << *index;
    };
    instructions[','] = [&, this] () {
        *index = getchar();
    };
    instructions['['] = [&, this] () {
        std::cout << "Begin Brace\n";
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
    instructions[']'] = [&, this] () {
        std::cout << "End Brace\n";
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
    /*instructions['@'] = [this] () {
        exit(0);
    };
    instructions['$'] = [this] () {
        storage = tape[index];
    };
    instructions['!'] = [this] () {
        tape[index] = storage;
    };
    instructions['}'] = [this] () {
        tape[index] >>= 1;
    };
    instructions['{'] = [this] () {
        tape[index] <<= 1;
    };
    instructions['~'] = [this] () {
        tape[index] = ~tape[index];
    };
    instructions['^'] = [this] () {
        tape[index] ^= storage;
    };
    instructions['&'] = [this] () {
        tape[index] &= storage;
    };
    instructions['|'] = [this] () {
        tape[index] |= storage;
    };*/


}

Brainfuck::~Brainfuck()
{
    //dtor
}

void Brainfuck::open()
{
    file.open(filename);

    if (!file.good()) throw std::runtime_error("Could not open file \"" + filename + "\"!  Does it really exist?");

    std::ostringstream temp;
    temp << file.rdbuf();

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

    if (!tempbracestack.empty())
        throw std::runtime_error("Program \"" + filename + "\" does not balance braces ([]) correctly!");
}

void Brainfuck::nextInstruction()
{
    //std::cout << currentinstruction << std::endl;
    try {
        instructions.at(*currentinstruction)();
    }
    catch (std::out_of_range) {
    }
    currentinstruction++;
}
