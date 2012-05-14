#include "brainfuck.h"
#include <iostream>
#include <array>
#include <stack>
using namespace std;

Brainfuck::Brainfuck()
{
    bf_program.open(getFileName());
}

Brainfuck::Brainfuck(char* args[])
{
    try {
        bf_program.open(args[1]);
    }
    catch (...) {
        cout << "Command line argument not found!";
    }
}

Brainfuck::~Brainfuck()
{
    //dtor
}

bool Brainfuck::bracketsOK()
{

}

string Brainfuck::getFileName()
{
    string theFileName;
    cout << "Enter the name and location of the file you wish to use.\n";
    getline(cin, theFileName);
    return theFileName;
}

void Brainfuck::readProgram()
{
    //The memory for an ordinary Brainfuck program.  Will be replaced later.  Named for the official definition.
    std::array<unsigned char, 30000> tape;


    unsigned char* ptr = tape;
    //A pointer for navigating the tape.

    stack<int> jumpPosition;
    //A stack to be used in loops with [].  Stores the position for the pointer to jump back to.

    unsigned char nextChar;
    //The character that will be analyzed by the switch statement below.

    while (bf_program.good()) {
        nextChar = bf_program.get();
        switch (nextChar)
        {
            case '+':
                ++*ptr;
                break;
            case '-':
                --*ptr;
                break;
            case '<':
                --ptr;
                break;
            case '>':
                ++ptr;
                break;
            case '.':
                cout << static_cast<unsigned char>(*ptr);
                break;
            case ',':
                *ptr = cin.get();
                break;
            case '[':
                if (*ptr) jumpPosition.push(bf_program.tellg());
                break;
            case ']':
                if (*ptr) { bf_program.seekg(jumpPosition.top()); continue; }
                else jumpPosition.pop();
                break;
            default:
                break;
        }
    }
}
