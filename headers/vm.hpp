#ifndef __JAM_VM__
#define __JAM_VM__

#include "includes.hpp"

class VM
{
    public:
    std::vector<unsigned char> m_vExecutable;
    std::vector<unsigned char> m_vEncryptedExecutable;

    public:
    bool init(std::vector<unsigned char>);
    std::vector<unsigned char> protect(std::string key);
    void pack();

    static void convertBinToSource(const std::string& binFile, const std::string& cppFile);
    private:
    private:
        uint8_t hash_1b(std::string seed)
        {
            uint8_t key = VM_KEY;
            for (size_t i = 0; i < seed.size(); i++)
            {
                key = ((key ^ seed[i]) * 0x83) ^ (key >> 3);
            }
            return key;
        }

};


#endif