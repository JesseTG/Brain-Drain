#ifndef ABSTRACTBF_H
#define ABSTRACTBF_H


class AbstractBF
{
    public:
        AbstractBF(const std::string& newfilename);
        virtual ~AbstractBF();

        std::string getFileName() const { return filename; }
        virtual void nextInstruction() = 0;

    protected:
        uint64_t currentinstruction;
        int64_t index;
        std::unordered_map<char, std::function<void()>> instructions;

    private:
        std::string filename;
        std::ifstream file;
};

#endif // ABSTRACTBF_H
