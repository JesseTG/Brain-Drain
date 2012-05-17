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






    protected:
        uint8_t storage;
        std::ifstream file;
        std::string program;
        std::vector<uint8_t> tape;
        std::stack<int64_t> jumpposition;



};

#endif // BRAINFUCK_H
