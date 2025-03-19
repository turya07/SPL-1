#include <iostream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <iomanip>
using namespace std;

// Function to calculate score from eatenFruits and elapsedTime
int calculateScore(int eatenFruits, int elapsedTime)
{
    return max(0, eatenFruits * 1000 - elapsedTime); // Example scoring logic
}

bool greaterScore(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second;
}
int main(const int argc, const char *const argv[])
{
    vector<pair<int, int>> fruitTimePairs = {{6, 8}, {0, 15}, {47, 28}, {15, 95}};
    vector<pair<int, int>> scores;
    ofstream file;
    file.open(argv[1], ios::out);

    if(!file.is_open())
    {
        cout << "no CSV file not found" << endl;
        return 1;
    }

    // Calculate scores and store in the scores vector
    for (int i = 0; i < fruitTimePairs.size(); i++)
    {
        auto &pair = fruitTimePairs[i];
        int score = calculateScore(pair.first, pair.second);
        scores.push_back({i, score});
    }

    // Sort scores in descending order
    sort(scores.begin(), scores.end(), greaterScore);

    // Print sorted scores
    for (auto score : scores)
    {
        cout << score.first << " : " << score.second << endl;
    }
    cout << endl;

    return 0;
}