#ifndef ABSTRACTBF_H
#define ABSTRACTBF_H

#include "Declarations.h"

class AbstractBF
{
    public:
        AbstractBF();
        AbstractBF(const std::string& newfilename) :
            filename(newfilename)
            {}
        virtual ~AbstractBF() {}
        virtual void open() = 0;
        virtual void run() = 0;

        std::string getFileName() const { return filename; }

    protected:
        virtual void nextInstruction() = 0;
        virtual void checkLoops() = 0;

        std::unordered_map<char, std::function<void()>> instructions;
        std::vector<uint8_t> tape;
        uint8_t *index;  //The cell we're currently at in the program's memory
        std::string filename;
        boost::regex pattern;
        std::ifstream file;

    private:
};

#endif // ABSTRACTBF_H
