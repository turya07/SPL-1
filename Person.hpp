#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
class Level
{
private:
    std::string levelName;
    std::string levelNumber;

public:
    Level();
    void setLevel(std::string levelName, std::string levelNumber);
    std::vector<std::string> getAll() { return {levelName, levelNumber}; }
    ~Level();
};

Level::Level()
{
}
void Level::setLevel(std::string levelName, std::string levelNumber)
{
    this->levelName = levelName;
    this->levelNumber = levelNumber;
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
    std::string getPlayerName() { return playerName; }
    std::string getLevel() { return level.getAll()[0] + " " + level.getAll()[1]; }
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