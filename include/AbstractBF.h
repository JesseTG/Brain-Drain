#ifndef ABSTRACTBF_H
#define ABSTRACTBF_H

#include "Declarations.h"

class AbstractBF
{
    public:
        AbstractBF();
        AbstractBF(const std::string& newfilename) :
            currentinstruction(0),
            index(0)
            {}
        virtual ~AbstractBF() {}
        virtual void open() = 0;

        std::string getFileName() const { return filename; }

    protected:
        virtual void nextInstruction() = 0;
        virtual void run() = 0;
        uint64_t currentinstruction;
        int64_t index;
        std::unordered_map<char, std::function<void()>> instructions;
        std::vector<uint8_t> tape;
        std::string filename;
        boost::regex pattern;
        std::ifstream file;

    private:


};

#endif // ABSTRACTBF_H
