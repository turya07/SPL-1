#include <SFML/Graphics.hpp>
#include <vector>

#define UP sf::Keyboard::W
#define DOWN sf::Keyboard::S
#define LEFT sf::Keyboard::A
#define RIGHT sf::Keyboard::D
#define SP sf::Keyboard::Space

class Block
{
public:
    Block(int width, float x, float y)
    {
        this->width = width;
        this->height = width;
        block.setSize(sf::Vector2f(width, width));
        block.setPosition(x, y);
        block.setFillColor(sf::Color::White);
        block.setOutlineColor(sf::Color::Black);
        block.setOutlineThickness(1);
        speed = width;
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

    void move(sf::Event ev, sf::Vector2f startBoundary, sf::Vector2f endBoundary, std::vector<std::vector<Block>> blocks)
    {
        if (ev.key.code == UP && block.getPosition().y > startBoundary.x + height)
        {
            block.move(0, -speed);
        }
        else if (ev.key.code == DOWN && block.getPosition().y < endBoundary.y - height)
        {
            block.move(0, speed);
        }
        else if (ev.key.code == LEFT && block.getPosition().x > startBoundary.x + width)
        {
            block.move(-speed, 0);
        }
        else if (ev.key.code == RIGHT && block.getPosition().x < endBoundary.x - width)
        {
            block.move(speed, 0);
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
    void autoMove() {

    }

private:
    int width;
    int height;
    int speed = 10;
    sf::Vector2f position;
    sf::RectangleShape block;
};