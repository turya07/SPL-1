#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Block.hpp"
#include <iostream>

#define BOX_DIMENSION 400
#define BLOCK_SIZE 20
class Game
{
public:
    Game()
    {
    }
    void playGame(std::string lv)
    {
        window.create(sf::VideoMode(BOX_DIMENSION * 2, BOX_DIMENSION * 2), "Escape The Cope");

        std::vector<std::vector<Block>> blocks;
        // read level from file
        
        std::string levelName = "./levels/" + lv + ".txt";
        std::ifstream file(levelName);
        if (!file.is_open())
        {
            std::cout << "Error opening file" << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<Block> row;
            for (int i = 0; i < line.size(); i++)
            {
                Block b(BLOCK_SIZE, i * BLOCK_SIZE, blocks.size() * BLOCK_SIZE);
                if (line[i] == '#')
                {
                    b.setColor(sf::Color::White);
                    b.setOutlineColor(sf::Color::Black);
                }
                else
                {
                    b.setColor(sf::Color::Transparent);
                    b.setOutlineColor(sf::Color::Transparent);
                }
                row.push_back(b);
            }
            blocks.push_back(row);
        }

        // for (int i = 0; i <= BOX_DIMENSION / BLOCK_SIZE; i++)
        // {
        //     blocks.push_back(std::vector<Block>());
        //     for (int j = 0; j <= BOX_DIMENSION / BLOCK_SIZE; j++)
        //     {
        //         if (i == 0 || j == 0 || i == BOX_DIMENSION / BLOCK_SIZE || j == BOX_DIMENSION / BLOCK_SIZE)
        //             blocks[i].push_back(Block(BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE));
        //         else
        //         {
        //             Block b(BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE);
        //             int RandomFactor = rand() % 2;
        //             if (RandomFactor == 1)
        //             {
        //                 b.setColor(sf::Color::Transparent);
        //                 b.setOutlineColor(sf::Color::Transparent);
        //             }
        //             else
        //             {
        //                 b.setColor(sf::Color::White);
        //                 b.setOutlineColor(sf::Color::Black);
        //             }
        //             blocks[i].push_back(b);
        //         }
        //     }
        // }

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

    std::string showMenu()
    {
        sf::Font font;
        if (!font.loadFromFile("./fonts/firacode.ttf"))
        {
            std::cout << "Error loading font" << std::endl;
            return "";
        }

        sf::Text title("Select Difficulty", font, 30);
        title.setPosition(BOX_DIMENSION - 100, 50);

        sf::Text easy("Easy", font, 20);
        easy.setPosition(BOX_DIMENSION - 50, 150);

        sf::Text medium("Medium", font, 20);
        medium.setPosition(BOX_DIMENSION - 50, 200);

        sf::Text hard("Hard", font, 20);
        hard.setPosition(BOX_DIMENSION - 50, 250);

        std::vector<sf::Text> levels;
        for (int i = 1; i <= 5; ++i)
        {
            sf::Text level(std::to_string(i), font, 20);
            level.setPosition(BOX_DIMENSION - 50, 300 + i * 50);
            levels.push_back(level);
        }

        std::string selectedLevel = "";

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (easy.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        selectedLevel = "easy/";
                    }
                    else if (medium.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        selectedLevel = "medium/";
                    }
                    else if (hard.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        selectedLevel = "hard/";
                    }

                    for (int i = 0; i < levels.size(); ++i)
                    {
                        if (levels[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            selectedLevel += std::to_string(i + 1);
                            return selectedLevel;
                        }
                    }
                }
            }

            window.clear();
            window.draw(title);
            window.draw(easy);
            window.draw(medium);
            window.draw(hard);
            for (auto &level : levels)
            {
                window.draw(level);
            }
            window.display();
        }

        return selectedLevel;
    }
    ~Game()
    {
    }

private:
    sf::RenderWindow window;
};