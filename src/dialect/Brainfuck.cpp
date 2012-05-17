#include "../include/Brainfuck.h"

Brainfuck::Brainfuck(const std::string& newfilename)
{
    filename = newfilename;
    current_instruction = 0;
    index = 0;

    instructions['>'] = [this] () {
        ++index;
        if (index >= tape.size()) tape.push_back(0);
    };
    instructions['<'] = [this] () {
        --index;
        if (index < 0) throw std::runtime_error("Error in program " + filename + "!  Pointer has fallen below 0!");
    };
    instructions['+'] = [this] () {
        ++tape[index];
    };
    instructions['-'] = [this] () {
        --tape[index];
    };
    instructions['.'] = [this] () {
        std::cout << tape[index];
    };
    instructions[','] = [this] () {
        tape[index] = getchar();
    };
    instructions['['] = [this] () {
        if (tape[index]) jumpposition.push(index);
    };
    instructions[']'] = [this] () {
        if (tape[index]) index = jumpposition.top();
        else jumpposition.pop();
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
    if (!file.good()) throw std::runtime_error("Could not open " + filename + "!  Does it really exist?");

    file >> program;
    std::regex pattern("[^(><+-.,[]@$!}{~^&|)]", std::regex_constants::basic);

}

void Brainfuck::nextInstruction()
{
    try {
        instructions.at(current_instruction++)();
    }
    catch (std::out_of_range) {
        return;
    }
}
