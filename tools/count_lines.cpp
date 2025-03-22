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
        if (line.length() > 0)
            ++lines;
    }

    file.close();
    return lines;
}
std::string optimizeFileName(std::string filename)
{
    std::string optimized = filename;
    int pos = filename.find_last_of("/");
    if (pos != std::string::npos)
    {
        optimized = filename.substr(pos + 1);
    }
    return optimized;
}
void optimizePadding(std::string &str, int len)
{
    int l = str.length();
    if (l < len)
    {
        for (int i = 0; i < len - l; i++)
        {
            str += " ";
        }
    }
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
        std::string leftCol = "Total lines in " + optimizeFileName(filename);
        optimizePadding(leftCol, 39);
        if (t != -1)
        {
            totalLines += t;
            std::cout << "\t" << i << ". " << leftCol << ":  " << t << std::endl;
        }
    }
    std::cout << "=========================================================" << std::endl;
    std::string leftCol = "Total Lines of C/C++ code";
    optimizePadding(leftCol, 50);
    std::cout << leftCol << ":  " << totalLines << std::endl;

    std::cout << "============================X============================" << std::endl
              << std::endl;

    return 0;
}
