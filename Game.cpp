#include "Game.h"

Game::Game(sf::RenderWindow &window) : window(window)
{
    colors = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};
    colorIndex = 0; 
    reFactorShape(radius);
    shape.setPosition(window.getSize().x / 2 - radius, window.getSize().y / 2 - radius);
    if (font.loadFromFile("fonts/firacode.ttf"))
    {
        std::cout << "Font loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "Font not loaded" << std::endl;
    }

    // Use the default font
    text.setFont(font);
    text.setString("Hello, world!");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(window.getSize().x / 2 ,
                     window.getSize().y / 2);
}

void Game::reFactorShape(float x)
{
    shape.setRadius(x);
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents();

        if (clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            clock.restart();
            colorIndex = (colorIndex + 1) % colors.size();
            shape.setFillColor(colors[colorIndex]);
        }

        window.clear();
        window.draw(shape);

        window.display();
    }
}
void Game::goLeft()
{
    if (position.x > 10.0f)
        shape.setPosition(position.x - 15.0f, position.y);
}
void Game::goRight()
{
    if (position.x < window.getSize().x - shape.getRadius() * 2 - 10.0f)
        shape.setPosition(position.x + 15.0f, position.y);
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

        if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            shape.setPosition(sf::Mouse::getPosition(window).x - radius, position.y);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            shape.setPosition(window.getSize().x / 2 - radius, position.y);
        }
        position = shape.getPosition();
    }
}