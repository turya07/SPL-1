#include "include/Game.hpp"

int main()
{
    Game *game = new Game();
    std::string levelName;
    std::string playerName;
    bool isFirstPlayer = true;

    playerName = game->getName();
    if (playerName == "")
    {
        return 0;
    }
    isFirstPlayer = game->chooseOption();

    do
    {
        if (isFirstPlayer)
            createServer();
        else
            joinServer();

    } while (true);

    if (isFirstPlayer)
        levelName = game->showMenu();

    std::cout << "Level Name: " << levelName << std::endl;

    // game->playGame(levelName, playerName);

    return 0;
}