#include "header.hpp"

#define BOX_DIMENSION (int)720
#define BLOCK_SIZE (int)20
#define TRANSPARENT sf::Color::Transparent
#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define RED sf::Color::Red
#define BLUE sf::Color::Blue
#define YELLOW sf::Color::Yellow

class Game
{
public:
    sf::RenderWindow window;

    Game()
    {
    }
    void initGame()
    {
        this->window.create(sf::VideoMode(BOX_DIMENSION, BOX_DIMENSION, 24), "Escape The Cope");
    }
    void playGame(std::string lv)
    {
        initGame();

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
                Block b(BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (blocks.size() + 1) * BLOCK_SIZE);
                if (line[i] == '#')
                {
                    b.setColor(WHITE);
                    b.setOutlineColor(TRANSPARENT);
                }
                else
                {
                    b.setColor(TRANSPARENT);
                    b.setOutlineColor(TRANSPARENT);
                }
                row.push_back(b);
            }
            blocks.push_back(row);
        }

        Block theif(BLOCK_SIZE, BLOCK_SIZE * 3, BLOCK_SIZE * 3);
        Block police1(BLOCK_SIZE, BLOCK_SIZE * 15, BLOCK_SIZE * 3);
        Block police2(BLOCK_SIZE, BLOCK_SIZE * 15, BLOCK_SIZE * 5);

        theif.setOutlineColor(WHITE);
        theif.setColor(RED);

        // police
        police1.setColor(BLUE);
        police2.setColor(YELLOW);


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    window.close();
                    return;
                }
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
        initGame();
        sf::Font font;
        if (!font.loadFromFile("./fonts/firacode.ttf"))
        {
            std::cout << "Error loading font" << std::endl;
            return "";
        }
        sf::Text hint("HELP: Press E/M/H for Easy,medium or hard.\nThen press 1 to 5 to continue...\n", font, 14);
        hint.setPosition(BOX_DIMENSION / 6, 90);
        hint.setFillColor(WHITE);
        sf::Text title("Escape The Cop", font, 30);
        title.setPosition(BOX_DIMENSION / 6, 50);

        sf::Text easy("Easy", font, 20);
        easy.setPosition(BOX_DIMENSION / 6, 150);

        sf::Text medium("Medium", font, 20);
        medium.setPosition(BOX_DIMENSION / 6, 200);

        sf::Text hard("Hard", font, 20);
        hard.setPosition(BOX_DIMENSION / 6, 250);

        easy.setFillColor(sf::Color::Green);
        medium.setFillColor(sf::Color::Yellow);
        hard.setFillColor(sf::Color::Red);

        std::vector<sf::Text> levels;
        for (int i = 1; i <= 5; ++i)
        {
            sf::Text level(std::to_string(i), font, 20);
            level.setPosition(BOX_DIMENSION / 6 + 20 * i, 280);
            level.setOutlineColor(WHITE);
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

                if (event.type == sf::Event::KeyPressed)
                {

                    if (event.key.code == sf::Keyboard::E)
                    {
                        selectedLevel = "easy/";
                        for (auto &lv : levels)
                        {
                            lv.setFillColor(sf::Color::Green);
                        }
                    }
                    else if (event.key.code == sf::Keyboard::M)
                    {
                        selectedLevel = "medium/";
                        for (auto &lv : levels)
                        {
                            lv.setFillColor(sf::Color::Yellow);
                        }
                    }
                    else if (event.key.code == sf::Keyboard::H)
                    {
                        selectedLevel = "hard/";
                        for (auto &lv : levels)
                        {
                            lv.setFillColor(sf::Color::Red);
                        }
                    }
                    // window.draw(hint);
                    // window.draw(easy);
                    // window.draw(medium);
                    // window.draw(hard);

                    for (int i = 0; i < levels.size(); ++i)
                    {
                        switch (event.key.code)
                        {
                        case sf::Keyboard::Num1:
                            selectedLevel += '1';
                            window.close();
                            return selectedLevel;
                        case sf::Keyboard::Num2:
                            selectedLevel += '2';
                            window.close();
                            return selectedLevel;
                        case sf::Keyboard::Num3:
                            selectedLevel += '3';
                            window.close();
                            return selectedLevel;
                        case sf::Keyboard::Num4:
                            selectedLevel += '4';
                            window.close();
                            return selectedLevel;
                        case sf::Keyboard::Num5:
                            selectedLevel += '5';
                            window.close();
                            return selectedLevel;
                        default:
                            break;
                        }
                    }
                }
            }

            window.clear();
            window.draw(title);
            window.draw(hint);
            window.draw(easy);
            window.draw(medium);
            window.draw(hard);
            if (selectedLevel.length() > 0)
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
};