#include <fstream>
#include <sstream>
#include "utils.h"

namespace Utils 
{
    std::string readFile(const std::string& filePath) {
        std::ifstream fileStream(filePath, std::ios::in);

        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::stringstream fileContent;
        fileContent << fileStream.rdbuf();
        fileStream.close();

        return fileContent.str();
    }
}