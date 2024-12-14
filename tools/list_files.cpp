#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::string> listFiles(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(directory)) {
        files.push_back(entry.path().string());
    }
    return files;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory>" << std::endl;
        return 1;
    }

    std::string directory = argv[1];
    std::vector<std::string> files = listFiles(directory);

    std::cout << "Files in directory " << directory << ":" << std::endl;
    for (const auto& file : files) {
        std::cout << file << std::endl;
    }

    return 0;
}
