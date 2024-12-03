#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "person.hpp"
#include "Block.hpp"
#include <fstream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(480, 480), "SFML Text Tutorial!");

    std::vector<std::vector<Block>> blocks;

    for (int i = 0; i < 30; i++)
    {
        blocks.push_back(std::vector<Block>());
        for (int j = 0; j < 30; j++)
        {
            blocks[i].push_back(Block(10, 10, i * 10, j * 10));
        }
    }

    Block theif(10, 10, 100, 100);
    theif.setOutlineColor(sf::Color::Red);
    theif.setColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                theif.move(event);
        }

        window.clear();
        for (auto &&blockx : blocks)
        {
            for (auto &&bxy : blockx)
            {
                bxy.draw(window);
            }
        }

        theif.draw(window);
        window.display();
    }

    return 0;
}