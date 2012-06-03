#include "../../include/dialect/Brainfuck_X1.h"

Brainfuck_X1::Brainfuck_X1(const std::string& newfilename)
{
    tape.reserve(30000);
    std::fill(tape.begin(), tape.end(), 0);

    index = tape.data();
    filename = newfilename;
    storage = 0;
    pattern = boost::regex("[^]><+.,[@$!}{~^&|-]", boost::regex::basic);
    initInstructions();
}

void Brainfuck_X1::initInstructions()
{
    Brainfuck::initInstructions();   //Calls the base class's version of this method
    instructions['@'] = [&, this] () {  //Exits the program immediately
        exit(EXIT_SUCCESS);
    };
    instructions['$'] = [&, this] () {  //Stores the value at the pointer into storage
        storage = *index;
    };
    instructions['!'] = [&, this] () {  //Places the value in storage in the value at the pointer
        *index = storage;
    };
    instructions['}'] = [&, this] () {  //Bit-shifts the value at the pointer to the right by one
        *index >>= 1;
    };
    instructions['{'] = [&, this] () {  //Bit-shifts the value at the pointer to the left by one
        *index <<= 1;
    };
    instructions['~'] = [&, this] () {  //Bitwise NOTs the value at the pointer
        *index = ~*index;
    };
    instructions['^'] = [&, this] () {  //Bitwise XORs the value at the pointer with the value in storage
        *index ^= storage;
    };
    instructions['&'] = [&, this] () {  //Bitwise ANDs the value at the pointer with the value in storage
        *index &= storage;
    };
    instructions['|'] = [&, this] () {  //Bitwise ORs the value at the pointer with the value in storage
        *index |= storage;
    };
}
