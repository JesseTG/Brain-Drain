#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <stack>
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>
#include <regex>

class Brainfuck
{
    public:
        Brainfuck(const std::string& newfilename);
        virtual ~Brainfuck();

        void open();

        std::string getFileName() const { return filename; }
        virtual void nextInstruction();

    protected:
        uint8_t storage;
        uint64_t current_instruction;
        int64_t index;
        std::string filename;
        std::ifstream file;
        std::string program;
        std::vector<uint8_t> tape;
        std::stack<int64_t> jumpposition;

        std::unordered_map<char, std::function<void()>> instructions;

};

#endif // BRAINFUCK_H
