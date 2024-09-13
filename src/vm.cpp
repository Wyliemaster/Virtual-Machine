#include "../headers/includes.hpp"

bool VM::init(std::vector<unsigned char> executable)
{
    this->m_vExecutable = executable;
    printf("m_vExecutable.size(): %llu\n", this->m_vExecutable.size());
    return this->m_vExecutable.size() != 0;
}

std::vector<unsigned char> VM::protect(std::string key)
{
    uint8_t hash = hash_1b(key);
    size_t size = m_vExecutable.size();

    this->m_vEncryptedExecutable.resize(size);

    for (size_t i = 0; i < size; i++)
    {
        this->m_vEncryptedExecutable[i] = this->m_vExecutable[i] ^ hash;
    }

    printf("m_vEncryptedExecutable.size(): %llu\n", this->m_vEncryptedExecutable.size());

    return this->m_vEncryptedExecutable;
}

void VM::pack()
{
    if (std::filesystem::create_directory("temp"))
    {
        IO::writeFile("temp/data.bin", this->m_vEncryptedExecutable);
        VM::convertBinToSource("temp/data.bin", "temp/data.h");

        std::string command = "g++ -std=c++17 -o packed data/stub.cpp";
        int result = std::system(command.c_str());
        if (result != 0)
        {
            std::cout << "There was an issue packing your executable" << std::endl;
        }
        IO::DeleteDirectory("temp");
    }
}

// ChatGPT
void VM::convertBinToSource(const std::string& binFile, const std::string& cppFile) {
    // Open the input binary file
    std::ifstream input(binFile, std::ios::binary);
    if (!input) {
        std::cerr << "Error opening input file: " << binFile << std::endl;
        return;
    }

    // Read the binary file into a vector
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close(); // Close the input file

    // Open the output CPP file
    std::ofstream output(cppFile);
    if (!output) {
        std::cerr << "Error opening output file: " << cppFile << std::endl;
        return;
    }

    // Write the data array to the output file
    output << "const unsigned char DATA[] = {";
    for (size_t i = 0; i < buffer.size(); ++i) {
        if (i > 0) output << ", ";
        output << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
    }
    output << "};\n";
    output << "const unsigned int DATA_LEN = " << std::dec << buffer.size() << ";\n";
    output.close(); // Close the output file
}
