#ifndef BRAINFUCK_X1_H
#define BRAINFUCK_X1_H

#include "./Brainfuck.h"


class Brainfuck_X1 : public Brainfuck
{
    public:
        Brainfuck_X1(const std::string& newfilename);
        ~Brainfuck_X1() {}
        virtual void initInstructions();

    private:

        uint8_t storage;
};

#endif // BRAINFUCK_X1_H
