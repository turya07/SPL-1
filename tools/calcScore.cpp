#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

#define INT int64_t
#define ZERO (INT)0
using namespace std;
typedef struct ScoreBlock
{
    string name;
    INT fruites;
    INT time;
    INT score = 0;
} ScoreBlock;
// Function to calculate score from eatenFruits and elapsedTime
INT calculateScore(INT eatenFruits, INT elapsedTime)
{
    INT baseScore = eatenFruits * 10000;
    INT quickBonus = max(ZERO, 50000 - elapsedTime);   // Bonus decreases as time increases
    INT timePenalty = max(ZERO, elapsedTime - 5000); // Penalty starts after 5 seconds
    double multiplier = 1.0;
    if (elapsedTime < 500) // If all fruits are eaten within 5 seconds
    {
        multiplier = 1.5;
    }
    else if (elapsedTime < 10000) // If all fruits are eaten within 10 seconds
    {
        multiplier = 1.2;
    }
    // Final score calculation
    INT finalScore = static_cast<INT>((baseScore + quickBonus - timePenalty) * multiplier);

    return max(ZERO, finalScore);
}

bool greaterScore(ScoreBlock &a, ScoreBlock &b)
{
    return a.score > b.score;
}

vector<ScoreBlock> readFile(const string &filename)
{
    vector<ScoreBlock> scores;
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return scores;
    }
    string line;
    while (getline(file, line))
    {
        ScoreBlock block;
        block.name = line.substr(0, line.find(";"));
        line.erase(0, line.find(";") + 1);
        block.fruites = stoi(line.substr(0, line.find(";")));
        line.erase(0, line.find(";") + 1);
        block.time = stoi(line);
        scores.push_back(block);
    }
    file.close();
    return scores;
}

int main(const int argc, const char *const argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    vector<ScoreBlock> scores = readFile(argv[1]);
    int laxLenghtName = 0;
    // Calculate scores and store in the scores vector
    for (auto &score : scores)
    {
        score.score = calculateScore(score.fruites, score.time);
        laxLenghtName = max(laxLenghtName, (int)score.name.length());
    }
    // Sort scores in descending order
    sort(scores.begin(), scores.end(), greaterScore);

    // Print sorted scores
    for (auto score : scores)
    {
        cout << score.name << setw(laxLenghtName - score.name.length() + 5) << " : " << score.score << "(" << score.fruites << ")" << "(" << score.time/1000 << ")" << endl;
    }
    cout << endl;

    return 0;
}