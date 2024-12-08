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
        block.setSize(sf::Vector2f(width, height));
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
            if (allowMove(blocks, UP))
                block.move(0, -speed);
        }
        if (ev.key.code == DOWN && block.getPosition().y < endBoundary.y - height)
        {
            block.move(0, speed);
        }
        if (ev.key.code == LEFT && block.getPosition().x > startBoundary.x + width)
        {
            block.move(-speed, 0);
        }
        if (ev.key.code == RIGHT && block.getPosition().x < endBoundary.x - width)
        {
            block.move(speed, 0);
        }
        if (ev.key.code == SP)
        {
            // assign to center of boundary
            // block.setPosition(endBoundary.x / 2, endBoundary.y / 2);
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
    int speed = 10;
    sf::Vector2f position;
    sf::RectangleShape block;

    bool allowMove(std::vector<std::vector<Block>> blocks, sf::Keyboard::Key key)
    {
        for (auto &&blockx : blocks)
        {
            for (auto &&bxy : blockx)
            {
                if (bxy.block.getFillColor() != sf::Color::Transparent)
                    switch (key)
                    {
                    case UP:
                        if (position.x == bxy.getPosition().x && position.y - height == bxy.getPosition().y)
                        {
                            return false;
                        }
                        break;
                    case DOWN:
                        if (position.x == bxy.getPosition().x && position.y + height == bxy.getPosition().y)
                        {
                            return false;
                        }
                        break;
                    case LEFT:
                        if (position.y == bxy.getPosition().y && position.x - width == bxy.getPosition().x)
                        {
                            return false;
                        }
                        break;
                    case RIGHT:
                        if (position.y == bxy.getPosition().y && position.x + width == bxy.getPosition().x)
                        {
                            return false;
                        }
                        break;
                    default:
                        break;
                    }
            }
        }
        return true;
    }
};