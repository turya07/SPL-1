#include "include/Game.hpp"

int main()
{
    Game *game = new Game();
    std::string levelName;
    std::string playerName;

    playerName = game->getName();
    if (playerName == "")
    {
        return 0;
    }
    while (true)
    {
        bool willQuit = game->chooseOption();
        if (willQuit)
        {
            std::cout << "Quitting the game" << std::endl;
            exit(EXIT_SUCCESS);
        }
        game->server_client_UI();
        levelName = game->showMenu();
        std::cout << "Level Name: " << levelName << std::endl;
        game->playGame(levelName, playerName);
    }

    return 0;
}