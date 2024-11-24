#include "Game.h"

Game::Game(sf::RenderWindow &window) : window(window)
{

    colors = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};
    colorIndex = 0;
    reFactorShape(radius);
    shape.setPosition(window.getSize().x / 2 - radius, window.getSize().y - radius * 2 - 5.0f);

    // load font
    if (font.loadFromFile("fonts/firacode.ttf"))
    {
        std::cout << "Font loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "Font not loaded" << std::endl;
    }

    // Use the default font
    font.setSmooth(true);
    text.setFont(font);
    text.setCharacterSize(24);
    std::string scoreText = "Score: " + std::to_string(score);
    text.setString(scoreText);
    text.setFillColor(sf::Color::White);
    text.setPosition(window.getSize().x / 2 - text.getCharacterSize(), 0);
    std::cout << "Text position: " << text.getPosition().x << " " << text.getPosition().y << std::endl;
    std::cout << text.getCharacterSize() << std::endl;
}

void Game::reFactorShape(float x)
{
    shape.setRadius(x);
}

void Game::createRandomObjects(int n, sf::RenderWindow &window)
{
    dots = std::vector<Dot>();
    for (int i = 0; i < n; i++)
    {
        float x = rand() % window.getSize().x;
        float y = rand() % window.getSize().y;
        sf::Color color = colors[rand() % colors.size()];
        Dot *dot = new Dot(x, y, 2.5f, color);
        dots.push_back(*dot);
    }
}

void Game::drawObjects(sf::RenderWindow &window)
{
    // update positons of each dot
    for (auto &&dot : dots)
    {
        dot.updatePosition(0.0f, 2.0f);

        dot.draw(window);
    }
}

void Game::updateScore()
{
    std::string scoreText = "Score: " + std::to_string(score);
    for (auto &&dot : dots)
    {
        if (dot.checkTouched(shape))
        {
            score++;
            dots.erase(dots.begin());
        }
    }

    text.setString(scoreText);
}

void Game::run()
{
    sf::Clock clock;
    createRandomObjects(50, window);
    shape.setFillColor(sf::Color::White);
    while (window.isOpen())
    {
        handleEvents();

        // update screen by 1s
        if (clock.getElapsedTime().asMilliseconds() > 150)
        {

            window.clear();
            drawObjects(window);
            updateScore();
            clock.restart();
        }
        window.draw(text);
        window.draw(shape);
        window.display();
    }
}

void Game::goLeft()
{
    if (position.x > 10.0f)
        shape.move(-15.0f, 0);
}

void Game::goRight()
{
    if (position.x < window.getSize().x - radius * 2 - 10.0f)
        shape.move(15.0f, 0);
}

void Game::handleEvents()
{
    while (window.pollEvent(event))
    {
        // std::cout << event.key.code << std::endl;
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }

        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            // if (radius < 200.f)
            //     radius += 10.f;
            goRight();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            // if (radius > 20.f)
            //     radius -= 10.f;
            goLeft();
        }

        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            shape.setPosition(window.getSize().x / 2 - radius, position.y);
        }
        position = shape.getPosition();
    }
}