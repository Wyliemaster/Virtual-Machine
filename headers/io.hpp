#ifndef __JAM_IO__
#define __JAM_IO__

#include "includes.hpp"

class IO
{
    public:
    static void writeFile(const std::string& filepath, const std::vector<uint8_t>& data);
    static std::vector<uint8_t> readFile(const std::string& filepath);
    static bool DeleteDirectory(const std::string& dirPath);
};

#endif