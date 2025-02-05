// built-in c++ lib
#include <iostream>
#include <fstream>
#include <vector>

// graphics lib
#include <SFML/Graphics.hpp>

// local lib
#include "Block.hpp"
#include "TimeBox.hpp"
#include "LoadImage.hpp"
#include "Person.hpp"

// CONST COLOR
#define TRANSPARENT sf::Color::Transparent
#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define RED sf::Color::Red
#define BLUE sf::Color::Blue
#define CYAN sf::Color::Cyan
#define YELLOW sf::Color::Yellow
#define GREEN sf::Color::Green

// CONST SIZE
#define BOX_DIMENSION (int)912
#define BLOCK_SIZE (int)16
#define GAP (int)20

// take alphabet and numeric key and return the character
char keyCodeToAlpha(sf::Event::KeyEvent key)
{
    if (key.code >= sf::Keyboard::A && key.code <= sf::Keyboard::Z)
    {
        return key.code + 65;
    }
    else if (key.code >= sf::Keyboard::Num0 && key.code <= sf::Keyboard::Num9)
    {
        return key.code + 22;
    }
    return ' ';
}

// SAVE data into file
bool saveDataIntoFile(std::string &sname, std::string &sage)
{
    std::ofstream file(sname + "data.txt");
    if (file.is_open())
    {
        // trim leading and trailing spaces
        sname.erase(0, sname.find_first_not_of(" "));
        sname.erase(sname.find_last_not_of(" ") + 1);
        sage.erase(0, sage.find_first_not_of(" "));
        sage.erase(sage.find_last_not_of(" ") + 1);

        // check if age is a number
        if (sage.find_first_not_of("0123456789") != std::string::npos)
        {
            return false;
        }
        else if (sname.length() == 0 || sage.length() == 0)
        {
            return false;
        }
        file << sname << "," << sage << std::endl;
        file.close();
        return true;
    }
    return false;
}
class Game
{
public:
    sf::RenderWindow window;

    Game();

    void initGame()
    {
        this->window.create(sf::VideoMode(BOX_DIMENSION, BOX_DIMENSION * 3 / 4), "Escape The Cop", sf::Style::Close | sf::Style::Titlebar);
        clock = sf::Clock();
        if (!font.loadFromFile("./fonts/exv.ttf"))
        {
            std::cout << "Error loading font" << std::endl;
        }
        title = sf::Text("Escape The Cop", font, 30);
    }

    void playGame(std::string lv, std::string plyName)
    {
        initGame();

        std::string lv1 = "";
        std::string lv2 = "";
        // police
        Block police1(BLOCK_SIZE, BLOCK_SIZE * 9, BLOCK_SIZE * 3 + 100);
        Block police2(BLOCK_SIZE, BLOCK_SIZE * 6, BLOCK_SIZE * 3 + 100);

        int getSlash = 0;
        for (int i = 0; i < lv.length(); i++)
        {
            if (lv[i] == '/')
            {
                getSlash = 1;
            }
            if (getSlash == 0)
            {
                lv1 += lv[i];
            }
            else if (getSlash == 1 && lv[i] != '/')
            {
                lv2 += lv[i];
            }
        }
        player.assignPerson(plyName, 0, lv1, lv2);
        timebox = TimeBox(font, WHITE, BOX_DIMENSION, GAP);

        scoreBoard.setFont(font);
        scoreBoard.setCharacterSize(16);
        scoreBoard.setString("Score: 00");
        scoreBoard.setFillColor(GREEN);
        scoreBoard.setPosition(BOX_DIMENSION - 16 * 16, GAP * 2);

        playerInfo.setFont(font);
        playerInfo.setCharacterSize(16);
        playerInfo.setString("Player: " + plyName);
        playerInfo.setFillColor(YELLOW);
        playerInfo.setPosition(BOX_DIMENSION - 16 * 16, GAP * 3);

        otherInfo.setFont(font);
        otherInfo.setCharacterSize(16);
        otherInfo.setString("WHITE: Theif\nRED & YELLOW: Police\nPINK: 1 point/Fruit\n");
        otherInfo.setFillColor(WHITE);
        otherInfo.setPosition(BOX_DIMENSION - 16 * 16, GAP * 4);

        levelInfo.setFont(font);
        levelInfo.setCharacterSize(16);
        levelInfo.setString("Level: " + lv + "\nCtrl+[SPACE] to Exit");
        levelInfo.setFillColor(RED);
        levelInfo.setPosition(BOX_DIMENSION - 16 * 16, GAP * 7);

        // read level from file
        std::string levelName = "./levels/" + lv + ".txt";
        std::ifstream file(levelName);
        if (!file.is_open())
        {
            std::cout << "Error opening file" << std::endl;
            return;
        }
        std::string line;
        int numOfSpace = 0;
        int idx, idy;
        idx = idy = -1;
        while (std::getline(file, line))
        {
            std::vector<Block> row;
            std::vector<Block> fruitRow;

            idx++;

            for (int i = 0; i < line.size(); i++)
            {
                ID id = {idx, i};
                Block b(BLOCK_SIZE, (i + 1) * BLOCK_SIZE, (blocks.size() + 1) * BLOCK_SIZE + 100, id);             // single BLOCK
                Block f(BLOCK_SIZE / 2, (i + 1) * BLOCK_SIZE + 4, (blocks.size() + 1) * BLOCK_SIZE + 4 + 100, id); // single FRUIT
                if (line[i] == '#')
                {
                    b.setColor(sf::Color(20, 80, 170, 255));
                    b.setOutlineColor(BLACK);
                }
                else
                {
                    switch (line[i])
                    {
                    case '1':
                        police1.setPosition(b.getPosition());
                        break;
                    case '2':
                        police2.setPosition(b.getPosition());
                        break;
                    default:
                        b.setColor(TRANSPARENT);
                        b.setOutlineColor(TRANSPARENT);
                        f.setColor(sf::Color::Magenta);
                        numOfSpace++;
                        if (numOfSpace % 3 == 0)
                        {
                            fruitRow.push_back(f);
                        }
                        break;
                    }
                }
                row.push_back(b);
            }
            blocks.push_back(row);
            fruits.push_back(fruitRow);
        }

        Block theif(BLOCK_SIZE, BLOCK_SIZE * 3, BLOCK_SIZE * 3 + 100);

        theif.setOutlineColor(TRANSPARENT);
        theif.setColor(WHITE);

        police1.setColor(RED);
        police2.setColor(YELLOW);

        std::cout << "Game Started" << std::endl;
        std::cout << player.getPlayerName() << std::endl;
        std::cout << player.getLevel() << std::endl;

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && event.key.control == true)
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
            for (auto &&fx : fruits)
            {
                for (auto &&fxy : fx)
                {
                    if (fxy.getPosition().x - 4 == theif.getPosition().x && fxy.getPosition().y - 4 == theif.getPosition().y && fxy.getSize().x != 0 && fxy.getSize().y != 0)
                    {
                        score++;
                        std::string pad = score < 10 ? "0" : "";
                        scoreBoard.setString("Score: " + pad + std::to_string(score));
                        player.updateScore(score);
                        fxy.deleteIt();
                    }
                    fxy.draw(window);
                }
            }
            time = (int)clock.getElapsedTime().asSeconds();

            window.draw(title);
            theif.draw(window);
            police1.draw(window);
            police2.draw(window);
            window.draw(levelInfo);
            window.draw(playerInfo);
            window.draw(otherInfo);
            window.draw(scoreBoard);
            timebox.draw(window, time);
            texture.draw(window);
            window.display();
        }

        return;
    }

    std::string getName()
    {
        initGame();
        std::string defNam = "Enter Your Name: ";
        sf::Text name(defNam, font, 20);
        sf::Text info("Press Enter to continue\n", font, 16);
        name.setPosition(BOX_DIMENSION / 6, 150);
        name.setFillColor(WHITE);

        info.setPosition(BOX_DIMENSION / 6, 130);
        info.setFillColor(WHITE);

        std::string playerName = "";
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    if (playerName.length() < 3)
                    {
                        window.close();
                        return "";
                    }
                }

                else if (event.type == sf::Event::KeyPressed)
                {

                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }

                    else if (event.key.code == sf::Keyboard::BackSpace)
                    {
                        if (playerName.size() > 0)
                        {
                            playerName.pop_back();
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Return)
                    {
                        if (playerName.length() < 3)
                        {
                            info.setString("Name must be at least 3 characters\n");
                        }
                        else
                        {
                            window.close();
                        }
                    }
                    else
                    {
                        playerName += keyCodeToAlpha(event.key);
                    }
                }
            }

            name.setString(defNam + " " + playerName + "_");

            window.clear();
            window.draw(name);
            window.draw(title);
            window.draw(info);
            window.display();
        }

        return playerName;
    }

    std::string showMenu()
    {
        initGame();
        sf::Text hint("HELP: Press E/M/H for Easy,medium or hard.\n      Then press 1 to 5 to Select Level Number\n      The color in number indicates for which type of levels are you choosing a level?\n      Press CTRL+W to view HIGH SCORE.", font, 14);
        hint.setPosition(BOX_DIMENSION / 6, GAP * 5);
        hint.setFillColor(WHITE);

        sf::Text easy("Easy", font, 20);
        easy.setPosition(BOX_DIMENSION / 6, GAP * 7.5 + 14 * 4);

        sf::Text medium("Medium", font, 20);
        medium.setPosition(BOX_DIMENSION / 6, GAP * 9 + 14 * 4);

        sf::Text hard("Hard", font, 20);
        hard.setPosition(BOX_DIMENSION / 6, GAP * 10.5 + 14 * 4);

        sf::Text status("", font, 18);
        status.setPosition(BOX_DIMENSION / 6, GAP * 12 + 14 * 4);
        status.setFillColor(CYAN);

        easy.setFillColor(sf::Color::Green);
        medium.setFillColor(sf::Color::Yellow);
        hard.setFillColor(sf::Color::Red);

        std::vector<sf::Text> levels;
        for (int i = 0; i <= 4; ++i)
        {
            sf::Text level(std::to_string(i + 1), font, 20);
            level.setPosition(BOX_DIMENSION / 6 + 20 * i, easy.getPosition().y - 20);
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
                    if (event.key.code == sf::Keyboard::W && event.key.control == true)
                    {

                        // read scores from score/data.csv where each line has name,score,time_in_seconds by semicolon separated
                        std::ifstream scoreFile("scores/data.csv");
                        if (!scoreFile.is_open())
                        {
                            std::cout << "Error opening score file" << std::endl;
                        }
                        else
                        {
                            std::string scoreLine;
                            std::string scoreData = "High Scores:\n";
                            while (std::getline(scoreFile, scoreLine))
                            {
                                std::string name,
                                    score,
                                    time;

                                name = scoreLine.substr(0, scoreLine.find(";"));
                                scoreLine.erase(0, scoreLine.find(";") + 1);
                                score = scoreLine.substr(0, scoreLine.find(";"));
                                scoreLine.erase(0, scoreLine.find(";") + 1);
                                time = scoreLine;
                                scoreData += name + "\t" + score + "\t" + time + "s\n";
                            }
                            std::cout << scoreData << std::endl;
                            scoreFile.close();
                            status.setString("Selected Level: " + selectedLevel.substr(0, selectedLevel.length() - 1) + "\n" + scoreData);
                        }
                    }

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
            window.draw(status);
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
    unsigned int score = 0;
    int time = 0;

    sf::Font font;
    sf::Text title;
    sf::Text levelInfo;
    sf::Text otherInfo;
    sf::Text scoreBoard;
    sf::Clock clock;
    sf::Text playerInfo;

    std::vector<std::vector<Block>> blocks;
    std::vector<std::vector<Block>> fruits;

    bool isShowScoreBoard = false;

    Person player;
    TimeBox timebox;
    LoadImage texture;
};

Game::Game()
{
    std::cout << "Initializing game..." << std::endl;
}