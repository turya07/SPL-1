#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Function to calculate score from eatenFruits and elapsedTime
int calculateScore(int eatenFruits, int elapsedTime)
{
    return eatenFruits * 1000 - elapsedTime; // Example scoring logic
}

bool operator>(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second > b.second;
}

int main()
{
    vector<pair<int, int>> fruitTimePairs = {{6, 8}, {0, 15}, {47, 28}, {15, 95}};
    vector<pair<int, int>> scores;

    // Calculate scores and store in the scores vector
    for (int i = 0; i < fruitTimePairs.size(); i++)
    {
        auto &pair = fruitTimePairs[i];
        int score = calculateScore(pair.first, pair.second);
        scores.push_back({i, score});
    }

    // Sort scores in descending order
    sort(scores.begin(), scores.end(), greater<pair<int, int>>());

    // Print sorted scores
    for (auto score : scores)
    {
        cout << score.first << " : " << score.second << endl;
    }
    cout << endl;

    return 0;
}