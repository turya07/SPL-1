#include "LoadImage.hpp"

// Level Class
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

// Person Class
class Person
{

public:
    Person();
    void assignPerson(std::string, unsigned int, std::string, std::string, std::string, sf::Font);
    void updateScore(unsigned int score);
    int getScore() { return score; }
    void updateLevel(std::string, std::string);
    void deleteIt();
    void draw(sf::RenderWindow &window)
    {
        // std::cout << "Drawing Player: " << playerInfo.getString().toAnsiString() << std::endl;
        sprite.draw(window);
        // window.draw(playerInfo);
    }

    void move(sf::Vector2f pos)
    {
        sprite.move(pos);
    }

    // getter
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
    std::string playerName;
    sf::Text playerInfo;
    unsigned int playerId;
    unsigned int score;
    Level level;
    LoadImage sprite;
};
Person::Person()
{
    score = 0;
    playerName = "Player";
    level.setLevel("easy", "1");
    sprite = LoadImage();
}
void Person::assignPerson(std::string playerName, unsigned int playerId, std::string levelName, std::string levelNumber, std::string spritePath, sf::Font font)
{
    this->playerName = playerName.length() > 0 ? playerName : "Player " + std::to_string(playerId);
    this->playerId = playerId;
    this->score = 0;
    this->level.setLevel(levelName, levelNumber);
    this->sprite = LoadImage(spritePath, (int)playerId);

    this->playerInfo = sf::Text("Player: " + playerName, font, 16);
    this->playerInfo.setFillColor(YELLOW);
    this->playerInfo.setPosition(WIDTH - 16 * 16, GAP * 3);
}
void Person::updateScore(unsigned int score)
{
    this->score = score;
}
void Person::updateLevel(std::string levelName, std::string levelNumber)
{
    level.setLevel(levelName, levelNumber);
}
void Person::deleteIt()
{
    score = 0;
    sprite.~LoadImage();
}
Person::~Person()
{
}