#include <SFML/Graphics.hpp>
#include <vector>
#include "Block.hpp"

#define BOX_DIMENSION 400
#define BLOCK_SIZE 20
class Game
{
public:
    Game()
    {
    }
    void playGame()
    {
        sf::RenderWindow window(sf::VideoMode(600, 600), "Escape The Cope");

        std::vector<std::vector<Block>> blocks;

        for (int i = 0; i <= BOX_DIMENSION / BLOCK_SIZE; i++)
        {
            blocks.push_back(std::vector<Block>());
            for (int j = 0; j <= BOX_DIMENSION / BLOCK_SIZE; j++)
            {
                if (i == 0 || j == 0 || i == BOX_DIMENSION / BLOCK_SIZE || j == BOX_DIMENSION / BLOCK_SIZE)
                    blocks[i].push_back(Block(BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE));
                else
                {
                    Block b(BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE);
                    int RandomFactor = rand() % 2;
                    if (RandomFactor == 1)
                    {
                        b.setColor(sf::Color::Transparent);
                        b.setOutlineColor(sf::Color::Transparent);
                    }
                    else
                    {
                        b.setColor(sf::Color::White);
                        b.setOutlineColor(sf::Color::Black);
                    }
                    blocks[i].push_back(b);
                }
            }
        }

        Block theif(BLOCK_SIZE, BOX_DIMENSION / 2, BOX_DIMENSION / 2);
        theif.setOutlineColor(sf::Color::White);
        theif.setColor(sf::Color::Red);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed)
                    theif.move(event, blocks.front().front().getPosition(), blocks.back().back().getPosition(), blocks);
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

        return;
    }
    ~Game()
    {
    }

private:
};