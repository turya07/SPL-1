// #include "header.hpp"
#include "Game.hpp"

int main()
{
    Game *game = new Game();
    std::string levelName;

    levelName = game->showMenu();
    std::cout << "Level Name: " << levelName << std::endl;

    game->playGame(levelName);

    return 0;
}