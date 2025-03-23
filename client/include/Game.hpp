#include "Header.hpp"

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
bool saveDataIntoFile(std::string name, std::string score, std::string time, std::string gameType)
{
    std::cout << gameType << std::endl;
    std::string filePath = "db/" + gameType + "/data.csv";
    std::ofstream file(filePath, std::ios::app);
    if (!file.is_open())
    {
        // may be the file is on available, so create the file in that directory
        std::cout << "Creating new file" << std::endl;
        std::ofstream newFile(filePath);
        newFile.close();
        file.open(filePath, std::ios::app);
        if (!file.is_open())
        {
            std::cout << "Failed to create new file" << std::endl;

            return false;
        }
    }; // just escape the warning and re-conditioning
    if (file.is_open())
    {
        // trim leading and trailing spaces
        name.erase(0, name.find_first_not_of(" "));
        name.erase(name.find_last_not_of(" ") + 1);

        // check if score is a number
        if (score.find_first_not_of("0123456789") != std::string::npos)
        {
            return false;
        }
        else if (name.length() == 0 || score.length() == 0 || time.length() == 0)
        {
            return false;
        }
        file << std::endl
             << name << ";" << score << ";" << time;
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
    void initGame();
    std::string getName();
    std::string showMenu();
    void playGame(std::string, std::string);
    bool chooseOption();
    void server_client_UI();
    void showPauseMenu(bool);
    ~Game()
    {
    }

private:
    unsigned int score = 0; // SCORE Variable
    int64_t time = 0;
    int totalFruits = 0;
    bool isMenuOpen = false;
    bool isPlayerOne = true; // that denotes server if true else client
    bool isSoloMode = false;
    sf::Font font;
    sf::Text title = sf::Text("Escape The Cop", font, 30);
    sf::Text levelInfo;
    sf::Text otherInfo;
    sf::Text scoreBoard;
    sf::Clock clock;
    sf::Music music;

    std::vector<std::vector<Block>> blocks; // 2d matrix for WALL & GAPS
    std::vector<std::vector<Block>> fruits; // fruits as SCORE

    bool isShowScoreBoard = false;

    // Network objects
    Server *server = nullptr;
    Client *client = nullptr;

    // Person Info
    Person player1, player2;
    TimeBox timebox;

    std::string get_current_ip();
};

void Game::initGame()
{
    this->window.create(sf::VideoMode(WIDTH, HEIGHT), "Escape The Cop", sf::Style::Close | sf::Style::Titlebar);
    clock = sf::Clock();
    if (!font.loadFromFile("./assets/fonts/exv.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
    title.setPosition(WIDTH / 2 - title.getLocalBounds().width / 2, GAP);
    title.setFillColor(WHITE);
    sf::Image logo;
    if (!logo.loadFromFile("./assets/icons/logo.jpeg"))
    {
        std::cerr << "Failed to load logo" << std::endl;
        exit(EXIT_FAILURE);
    }
    window.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());
    window.setFramerateLimit(60);

    if (music.openFromFile("./assets/audio/police_music.ogg"))
    {
        music.setLoop(true);
        music.play();
        music.setVolume(30);
    }
    else
    {
        std::cerr << "Failed to load music" << std::endl;
    }
}

void Game::playGame(std::string lv, std::string plyName)
{
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
    player1.assignPerson(plyName, 1, lv1, lv2, ("./assets/icons/player_1.png"), font);
    if (!isSoloMode)
        player2.assignPerson(plyName, 2, lv1, lv2, ("./assets/icons/player_2.png"), font);

    timebox = TimeBox(font, WHITE, BOX_DIMENSION, GAP);

    scoreBoard.setFont(font);
    scoreBoard.setCharacterSize(16);
    scoreBoard.setString("Score: 00");
    scoreBoard.setFillColor(GREEN);
    scoreBoard.setPosition(WIDTH - 16 * 16, GAP * 2);

    otherInfo.setFont(font);
    otherInfo.setCharacterSize(16);
    otherInfo.setString("WHITE: Theif\nRED & YELLOW: Police\nPINK: 1 point/Fruit\n");
    otherInfo.setFillColor(WHITE);
    otherInfo.setPosition(WIDTH - 16 * 16, GAP * 4);

    levelInfo.setFont(font);
    levelInfo.setCharacterSize(16);
    levelInfo.setString("Level: " + lv + "\nEsc to Pause");
    levelInfo.setFillColor(RED);
    levelInfo.setPosition(WIDTH - 16 * 16, GAP * 7);

    // read level from file
    std::string levelName = "./levels/" + lv + ".txt";
    std::cout << levelName << std::endl;
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
            f.setColor(sf::Color::Magenta);
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
                case '*':
                    fruitRow.push_back(f);
                    totalFruits++;
                    b.setColor(TRANSPARENT);
                    b.setOutlineColor(TRANSPARENT);
                    break;
                default:
                    b.setColor(TRANSPARENT);
                    b.setOutlineColor(TRANSPARENT);
                    break;
                }
            }
            row.push_back(b);
        }
        blocks.push_back(row);
        fruits.push_back(fruitRow);
    }
    std::cout << "ALL blocked init\n";
    Block theif(BLOCK_SIZE, BLOCK_SIZE * 3, BLOCK_SIZE * 3 + 100);

    theif.setOutlineColor(TRANSPARENT);
    theif.setColor(WHITE);
    std::cout << "Theif set\n";
    police1.setColor(RED);
    police2.setColor(YELLOW);
    std::cout << "Polices set\n";

    std::cout << player1.getPlayerName() << std::endl;
    std::cout << player1.getLevel().first << " -- " << player1.getLevel().second << std::endl;
    std::cout << "Game Started" << std::endl;

    initGame();
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // if a match is over, delete everything
                blocks.clear();
                fruits.clear();
                police1.deleteIt();
                police2.deleteIt();
                theif.deleteIt();
                player1.deleteIt();
                if (!isSoloMode)
                {
                    player2.deleteIt();
                }
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    isMenuOpen = !isMenuOpen;
                }

                else if (event.key.code == sf::Keyboard::Space && event.key.control && isMenuOpen)
                {
                    this->scoreBoard.setString("Score: " + std::to_string(score) + ", Saving Data...");

                    // add score info to file in this sequence: NAME;SCORE;TIME
                    if (saveDataIntoFile(player1.getPlayerName(), std::to_string(score), std::to_string(time), player1.getLevel().first))
                    {
                        std::cout << "Data saved successfully" << std::endl;
                        this->scoreBoard.setString("Score: " + std::to_string(score) + ", Data Saved Successfully");
                        sf::sleep(sf::seconds(2));

                        window.close();
                        // if a match is over, delete everything
                        blocks.clear();
                        fruits.clear();
                        police1.deleteIt();
                        police2.deleteIt();
                        theif.deleteIt();
                        return;
                    }
                    else
                    {
                        this->scoreBoard.setString("Score: " + std::to_string(score) + ", Failed to save data");
                        sf::sleep(sf::seconds(2));
                        this->scoreBoard.setString("Score: " + std::to_string(score));
                    }
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    theif.move(event, blocks.front().front().getPosition(), blocks.back().back().getPosition(), blocks);
                }
            }
        }

        window.clear();
        if (isPlayerOne)
        {
            player1.move(theif.getPosition());
        }
        else if (!isSoloMode)
        {
            player2.move(theif.getPosition());
        }

        if (player1.getScore() == totalFruits && totalFruits != 0)
        {
            sf::Text congrats("Congratulations!", font, 36);
            sf::Text exitButton("Press Esc to show MENU", font, 16);
            congrats.setFillColor(GREEN);
            congrats.setPosition(WIDTH / 2 - congrats.getLocalBounds().width / 2, HEIGHT / 2);

            exitButton.setFillColor(YELLOW);
            exitButton.setPosition(WIDTH / 2 - exitButton.getLocalBounds().width / 2, HEIGHT / 2 + 36 + 16);
            window.draw(congrats);
            window.draw(exitButton);
            window.display();
            continue;
        }
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
                    player1.updateScore(score);
                    fxy.deleteIt();
                }
                fxy.draw(window);
            }
        }

        time = (int64_t)clock.getElapsedTime().asMilliseconds();

        window.draw(title);
        theif.draw(window);
        police1.draw(window);
        police2.draw(window);
        window.draw(levelInfo);
        player1.draw(window);
        // if (!isSoloMode)
        //     player2.draw(window);
        window.draw(otherInfo);
        window.draw(scoreBoard);
        timebox.draw(window, time);
        if (isMenuOpen)
        {
            showPauseMenu(isMenuOpen);
        }
        window.display();
    }

    // if a match is over, delete everything
    blocks.clear();
    fruits.clear();
    police1.deleteIt();
    police2.deleteIt();
    theif.deleteIt();
    player1.deleteIt();
    if (!isSoloMode)
    {
        player2.deleteIt();
    }
    return;
}

std::string Game::getName()
{
    initGame();
    std::string defNam = "Enter Your Name: ";
    sf::Text name(defNam, font, 20);
    sf::Text info("Press Enter to continue\n", font, 16);
    name.setPosition(WIDTH / 6, 150);
    name.setFillColor(WHITE);

    info.setPosition(WIDTH / 6, 130);
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

std::string Game::showMenu()
{
    initGame();
    bool willClientGetMsg = false;
    sf::Text hint("HELP: Press E/M/H for Easy,medium or hard.\n      Then press 1 to 5 to Select Level Number\n      The color in number indicates for which type of levels are you choosing a level?\n      Press CTRL+W to view HIGH SCORE.\n     Press CTRL+Enter to Continue.", font, 14);
    hint.setPosition(WIDTH / 6, GAP * 5);
    hint.setFillColor(WHITE);

    sf::Text easy("Easy", font, 20);
    easy.setPosition(WIDTH / 6, GAP * 7.5 + 14 * 6);

    sf::Text medium("Medium", font, 20);
    medium.setPosition(WIDTH / 6, GAP * 9 + 14 * 6);

    sf::Text hard("Hard", font, 20);
    hard.setPosition(WIDTH / 6, GAP * 10.5 + 14 * 6);

    sf::Text status("", font, 18);
    status.setPosition(WIDTH / 2, GAP * 7.5 + 14 * 6);
    status.setFillColor(GREEN);

    easy.setFillColor(sf::Color::Green);
    medium.setFillColor(sf::Color::Yellow);
    hard.setFillColor(sf::Color::Red);

    std::vector<sf::Text> levels;
    for (int i = 0; i <= 4; ++i)
    {
        sf::Text level(std::to_string(i + 1), font, 20);
        level.setPosition(WIDTH / 6 + 20 * i, easy.getPosition().y - 20);
        level.setOutlineColor(WHITE);
        levels.push_back(level);
    }

    std::string selectedLevel = "";
    int selectedLevelIndex = -1;

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
                    std::ifstream scoreFile("db/" + player1.getLevel().first + "/data.csv");
                    if (!scoreFile.is_open())
                    {
                        std::cout << "Error opening score file" << std::endl;
                    }
                    else
                    {
                        std::string scoreLine;
                        std::string scoreData = "Table of Scores: [" + player1.getLevel().first + "-" + std::to_string(selectedLevelIndex) + "]\n";
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
                        status.setString("\n" + scoreData);
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

                // this will send the selected level to the 2nd player if it is not solomode
                if (isPlayerOne && !isSoloMode)
                {
                    server->sendData(selectedLevel);
                }
                willClientGetMsg = false; // it will reset the client message
                if (!isSoloMode && !isPlayerOne && !willClientGetMsg)
                {
                    selectedLevel = client->getReceivedData();
                    willClientGetMsg = true;
                }
                if (isPlayerOne)
                {
                    for (int i = 0; i < levels.size(); ++i)
                    {
                        switch (event.key.code)
                        {
                        case sf::Keyboard::Num1:
                            selectedLevelIndex = 1;
                            break;
                        case sf::Keyboard::Num2:
                            selectedLevelIndex = 2;
                            break;
                        case sf::Keyboard::Num3:
                            selectedLevelIndex = 3;
                            break;
                        case sf::Keyboard::Num4:
                            selectedLevelIndex = 4;
                            break;
                        case sf::Keyboard::Num5:
                            selectedLevelIndex = 5;
                            break;
                        default:
                            break;
                        }
                    }
                    if (!isSoloMode)
                        server->sendData(selectedLevel + std::to_string(selectedLevelIndex));
                }

                if (event.key.code == sf::Keyboard::Enter && event.key.control && (isPlayerOne))
                {

                    window.close();
                    return selectedLevel + std::to_string(selectedLevelIndex);
                }

                player1.updateLevel(selectedLevel.substr(0, selectedLevel.length() - 1), std::to_string(selectedLevelIndex));
                if (!isSoloMode)
                    player2.updateLevel(selectedLevel.substr(0, selectedLevel.length() - 1), std::to_string(selectedLevelIndex));
            }
        }

        window.clear();
        window.draw(title);
        window.draw(hint);
        if (!isPlayerOne)
        {
            selectedLevel = client->getReceivedData();
            status.setString("Received Level: " + selectedLevel);
        }
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

    return selectedLevel + std::to_string(selectedLevelIndex);
}

bool Game::chooseOption()
{
    initGame();
    sf::Text option1("1. Create Server", font, 30);
    sf::Text option2("2. Join Server", font, 30);
    sf::Text option3("3. Solo Mode\nEsc: Quit the game", font, 30);

    sf::Text prompt("Choose an option:", font, 36);

    prompt.setPosition(WIDTH / 2 - prompt.getLocalBounds().width / 2, HEIGHT / 2 - 100);
    option1.setPosition(WIDTH / 2 - prompt.getLocalBounds().width / 2, HEIGHT / 2 - 50);
    option2.setPosition(WIDTH / 2 - prompt.getLocalBounds().width / 2, HEIGHT / 2);
    option3.setPosition(WIDTH / 2 - prompt.getLocalBounds().width / 2, HEIGHT / 2 + 50);

    prompt.setFillColor(WHITE);
    option1.setFillColor(WHITE);
    option2.setFillColor(WHITE);
    option3.setFillColor(WHITE);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return true;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    return true;
                }
                if (event.key.code == sf::Keyboard::Num1)
                {
                    this->isPlayerOne = true;
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    this->isPlayerOne = false;
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    this->isPlayerOne = true;
                    this->isSoloMode = true;
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(prompt);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.display();
    }

    return false;
}

void Game::server_client_UI()
{
    if (isSoloMode)
    {
        std::cout << "Solo Mode Choosen, starting play game..." << std::endl;
        return;
    }
    initGame();
    std::string tiltleName = (isSoloMode ? "" : isPlayerOne ? "Server"
                                                            : "Client");
    window.setTitle("Escape The Cop - " + tiltleName);

    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/exv.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
        return;
    }

    // Texts for UI
    sf::Text ipText, portText, statusText;
    ipText.setFont(font);
    portText.setFont(font);
    statusText.setFont(font);

    ipText.setString("IP Address: ");
    portText.setString("Port: ");
    statusText.setString("Status: Not Connected");

    ipText.setPosition(50, 70);
    portText.setPosition(50, 120);
    statusText.setPosition(50, 170);

    // Input boxes
    sf::RectangleShape ipBox(sf::Vector2f(200, 30));
    sf::RectangleShape portBox(sf::Vector2f(100, 30));

    ipBox.setPosition(200, 70);
    portBox.setPosition(200, 120);

    // Variables for input
    std::string ipInput, portInput, messageInput;
    bool isServer = isPlayerOne;
    if (isServer)
    {
        ipInput = get_current_ip();
        portInput = "8080";
    }
    bool isConnected = false;

    if (!isConnected && isPlayerOne)
    {
        server = new Server(std::stoi(portInput));
        statusText.setString("Status: Connected as Server. Wait for client to connect.\nDon't close the window.");
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (!isServer)
            { // Handle text input
                if (event.type == sf::Event::TextEntered)
                {
                    if (ipBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                    {
                        if (event.text.unicode == '\b' && !ipInput.empty())
                        {
                            ipInput.pop_back();
                        }
                        else if (event.text.unicode < 128)
                        {
                            ipInput += static_cast<char>(event.text.unicode);
                        }
                    }
                    else if (portBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                    {
                        if (event.text.unicode == '\b' && !portInput.empty())
                        {
                            portInput.pop_back();
                        }
                        else if (event.text.unicode < 128)
                        {
                            portInput += static_cast<char>(event.text.unicode);
                        }
                    }
                }

                // Handle mouse clicks for selecting input boxes
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (ipBox.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        {
                            ipBox.setOutlineThickness(2);
                            portBox.setOutlineThickness(0);
                        }
                        else if (portBox.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        {
                            portBox.setOutlineThickness(2);
                            ipBox.setOutlineThickness(0);
                        }

                        else
                        {
                            ipBox.setOutlineThickness(0);
                            portBox.setOutlineThickness(0);
                        }
                    }
                }
                // Handle Enter key for connection and sending messages
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (!isConnected)
                        {

                            client = new Client();
                            if (client->connect(ipInput, std::stoi(portInput)))
                            {
                                statusText.setString("Status: Connected as Client. Press enter to continue.");
                                isConnected = true;
                            }
                            else
                            {
                                statusText.setString("Status: Connection Failed");
                            }
                        }
                        else
                            window.close();
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                }
            }
            else
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                {
                    if (isConnected)
                    {
                        window.close();
                    }
                }
            }
        }

        // Clear the window
        window.clear();
        window.draw(title);
        // Draw UI elements

        window.draw(ipText);
        window.draw(portText);
        window.draw(statusText);
        window.draw(ipBox);
        window.draw(portBox);

        // Draw input text
        sf::Text ipInputText(ipInput, font, 20);
        sf::Text portInputText(portInput, font, 20);
        ipInputText.setPosition(205, 75);
        portInputText.setPosition(205, 125);

        ipInputText.setFillColor(sf::Color::Black);
        portInputText.setFillColor(sf::Color::Black);

        window.draw(ipInputText);
        window.draw(portInputText);

        // Display the window
        window.display();

        if (isServer && !isConnected)
        {
            server->run();
            isConnected = true;
            statusText.setString("Status: Connected as Server. Press Enter to continue.");
        }
    }

    return;
}

void Game::showPauseMenu(bool willShow)
{
    sf::Text pauseText("Game Paused", font, 56);
    pauseText.setPosition(WIDTH / 2 - pauseText.getLocalBounds().width / 2, HEIGHT / 2 - 150);
    pauseText.setFillColor(WHITE);

    sf::Text resumeText("Press Ctrl+Space to save current Data", font, 20);
    resumeText.setPosition(WIDTH / 2 - pauseText.getLocalBounds().width, HEIGHT / 2 - 50);
    resumeText.setFillColor(WHITE);

    sf::Text exitText("Press Q to Quit Game", font, 20);
    exitText.setPosition(WIDTH / 2 - pauseText.getLocalBounds().width, HEIGHT / 2);
    exitText.setFillColor(WHITE);

    if (willShow)
    {
        window.draw(pauseText);
        window.draw(resumeText);
        window.draw(exitText);
        return;
    }
}

std::string Game::get_current_ip()
{
    char buffer[128];
    std::string result = "";
    FILE *fp = popen("hostname -I", "r");
    if (fp == NULL)
    {
        std::cout << "Failed to run command" << std::endl;
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        result += buffer;
    }
    pclose(fp);
    return result;
}
Game::Game()
{
    std::cout << "Initializing game..." << std::endl;
}