#include "../../include/dialect/Brainfuck.h"

Brainfuck::Brainfuck(const std::string& newfilename)
{
    tape.reserve(30000);
    index = tape.data();
    std::fill(tape.begin(), tape.end(), 0);
    filename = newfilename;
    pattern = boost::regex("[^]><+.,[@$!}{~^&|-]", boost::regex::basic);

    instructions['>'] = [&, this] () {
        if (*index == tape.back()) tape.push_back(0);
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
        std::cout << *index;
    };
    instructions[','] = [&, this] () {
        *index = getchar();
    };
    instructions['['] = [&, this] () {
        if (*index == 0) {  //If the value under the pointer is 0, go past the matching ]
            std::stack<char> tempbracestack;

            while (true) {
                if (*currentinstruction == '[')
                    tempbracestack.push(*currentinstruction);
                else if (*currentinstruction == ']')
                    tempbracestack.pop();

                ++currentinstruction;
                if (tempbracestack.empty()) return;
            }
        }
    };
    instructions[']'] = [&, this] () {
        if (*index != 0) {  //If the value under the pointer isn't 0, go back to the matching [
            std::stack<char> tempbracestack;

            while (true) {
                if (*currentinstruction == ']')
                    tempbracestack.push(*currentinstruction);
                else if (*currentinstruction == '[')
                    tempbracestack.pop();

                --currentinstruction;
                if (tempbracestack.empty()) return;
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
    std::stack<char> tempbracestack;  //The indicies are the ['s, their elements are the ]'s

    for (char i : program) {
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
    catch (std::out_of_range e) {
    }
    currentinstruction++;
}
