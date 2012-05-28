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

        virtual void run();


    protected:
        virtual void nextInstruction();
        virtual void checkLoops();
        uint8_t storage;
        std::string program;
        char *currentinstruction;  //Which character in the program is being processed
};

#endif // BRAINFUCK_H
