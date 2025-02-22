#include <iostream>
#include <fstream>
#include <string>

int countLines(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return -1;
    }

    int lines = 0;
    std::string line;
    while (std::getline(file, line))
    {
        if(line.length() >0)
        ++lines;
    }

    file.close();
    return lines;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filenames>" << std::endl;
        return 1;
    }

    int n = argc;
    int totalLines = 0;
    for (int i = 1; i < argc; i++)
    {

        std::string filename = argv[i];
        int t = countLines(filename);
        if (t != -1)
        {
            totalLines += t;
            std::cout << "Total lines in " << filename << ": " << t << std::endl;
        }
    }
    std::cout << std::endl
              << "Total Lines of C code in this project: " << totalLines << std::endl
              << std::endl;
    return 0;
}
