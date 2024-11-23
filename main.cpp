#include "headers.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(450, 450), "SFML Game");
    Game game(window);
    game.run();

    return 0;
}