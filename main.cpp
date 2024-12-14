#include "header.hpp"

int main()
{
    Game game;
    std::string levelName;
    levelName = game.showMenu();
    std::cout << "Level Name: " << levelName << std::endl;
    game.playGame(levelName);
}