#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <fstream>
#include <string>
using namespace std;

class Brainfuck
{
    public:
        Brainfuck();
        Brainfuck(char* args[]);
        string getFileName();
        virtual void readProgram();
        virtual ~Brainfuck();
    protected:
        bool bracketsOK();
        fstream bf_program;
        string fileName;
    private:

};

#endif // BRAINFUCK_H
