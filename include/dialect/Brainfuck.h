#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include "../Declarations.h"
#include "../AbstractBF.h"

class Brainfuck : public AbstractBF
{
    public:
        Brainfuck() {}
        Brainfuck(const std::string& newfilename);
        virtual ~Brainfuck();
        virtual void open();
        virtual void nextInstruction();
        virtual void run() {}


    protected:
        uint8_t storage;
        std::string program;

        std::stack<int64_t> jumpposition;
};

#endif // BRAINFUCK_H
