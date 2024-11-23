#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");
    Game game(window);
    game.run();

    return 0;
}