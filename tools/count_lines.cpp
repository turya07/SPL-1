#include <iostream>
#include <fstream>
#include <string>

int countLines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return -1;
    }

    int lines = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++lines;
    }

    file.close();
    return lines;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int totalLines = countLines(filename);

    if (totalLines != -1) {
        std::cout << "Total lines in " << filename << ": " << totalLines << std::endl;
    }

    return 0;
}
