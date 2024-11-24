#include "headers.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game", sf::Style::Close);
    Game game(window);
    game.run();

    return 0;
}