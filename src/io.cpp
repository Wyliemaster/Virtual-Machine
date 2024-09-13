#include "../headers/includes.hpp"

void IO::writeFile(const std::string& filepath, const std::vector<uint8_t>& data) {
    std::ofstream file(filepath, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

std::vector<uint8_t> IO::readFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
}

bool IO::DeleteDirectory(const std::string& dirPath) {
    std::string searchPath = dirPath + "\\*"; // Path to search for files and directories
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open directory: " << dirPath << std::endl;
        return false;
    }

    do {
        const std::string fileOrDirName = findFileData.cFileName;

        if (fileOrDirName != "." && fileOrDirName != "..") {
            std::string fullPath = dirPath + "\\" + fileOrDirName;

            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                // Recursively delete subdirectories
                if (!DeleteDirectory(fullPath)) {
                    FindClose(hFind);
                    return false;
                }
            }
            else {
                // Delete files
                if (!DeleteFile(fullPath.c_str())) {
                    std::cerr << "Failed to delete file: " << fullPath << std::endl;
                    FindClose(hFind);
                    return false;
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData));

    FindClose(hFind);

    // Finally, remove the directory itself
    if (!RemoveDirectory(dirPath.c_str())) {
        std::cerr << "Failed to delete directory: " << dirPath << std::endl;
        return false;
    }

    return true;
}