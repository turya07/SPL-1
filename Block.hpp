#include <SFML/Graphics.hpp>

class Block
{
public:
    Block(int width, int height, float x, float y)
    {
        this->width = width;
        this->height = height;
        block.setSize(sf::Vector2f(width, height));
        block.setPosition(x, y);
        block.setFillColor(sf::Color::White);
        block.setOutlineColor(sf::Color::Black);
        block.setOutlineThickness(1);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(block);
    }

    sf::Vector2f getPosition()
    {
        return block.getPosition();
    }

    sf::Vector2f getSize()
    {
        return block.getSize();
    }
    void move(sf::Event ev)
    {
        if (ev.key.code == sf::Keyboard::W)
        {
            block.move(0, -10);
        }
        if (ev.key.code == sf::Keyboard::S)
        {
            block.move(0, 10);
        }
        if (ev.key.code == sf::Keyboard::A)
        {
            block.move(-10, 0);
        }
        if (ev.key.code == sf::Keyboard::D)
        {
            block.move(10, 0);
        }
    }

    void setPosition(sf::Vector2f position)
    {
        block.setPosition(position);
    }

    void setColor(sf::Color color)
    {
        block.setFillColor(color);
    }
    void setOutlineColor(sf::Color color)
    {
        block.setOutlineColor(color);
    }

    void setOutlineThickness(float thickness)
    {
        block.setOutlineThickness(thickness);
    }

private:
    int width;
    int height;
    sf::Vector2f position;
    sf::RectangleShape block;
};