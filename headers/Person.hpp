#include <iostream>
#include <vector>
#include <inttypes.h>
#include <SFML/Graphics.hpp>
class Level
{
private:
    std::string levelName;
    std::string levelNumber;

public:
    Level();
    void setLevel(std::string levelName, std::string levelNumber);
    int parseInt(std::string);
    std::pair<std::string, int> getAll() { return {levelName, parseInt(levelNumber)}; }
    ~Level();
};

Level::Level()
{
}
int Level::parseInt(std::string str)
{
    int num = 0;
    for (int i = 0; i < str.size(); i++)
    {
        num = num * 10 + (str[i] - '0');
    }
    return num;
}
void Level::setLevel(std::string levelName, std::string levelNumber)
{
    this->levelName = levelName;
    this->levelNumber = levelNumber;
    std::cout << "Setting level to " << levelName << " " << levelNumber << std::endl;
}
Level::~Level()
{
}

class Person
{
public:
    Person();
    void assignPerson(std::string playerName, unsigned int score, std::string levelName, std::string levelNumber);
    void updateScore(unsigned int score);
    int getScore() { return score; }
    std::string getPlayerName()
    {
        return playerName;
    }
    std::pair<std::string, int> getLevel()
    {
        return level.getAll();
    }
    ~Person();

private:
    unsigned int score;
    std::string playerName;
    Level level;
};

Person::Person()
{
    score = 0;
    playerName = "Player";
    level.setLevel("easy", "1");
}
void Person::assignPerson(std::string playerName, unsigned int score, std::string levelName, std::string levelNumber)
{
    this->playerName = playerName;
    this->score = score;
    this->level.setLevel(levelName, levelNumber);
}
void Person::updateScore(unsigned int score)
{
    this->score = score;
}
Person::~Person()
{
}