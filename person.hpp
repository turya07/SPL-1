#include <iostream>
#include <SFML/Graphics.hpp>

class Person
{
public:
    enum Type
    {
        Police,
        Thief
    };
    enum MoveType
    {
        Auto,
        Manual
    };

    Person(Type type, MoveType moveType, float speed, sf::Vector2f position)
        : type(type), moveType(moveType), speed(speed), position(position), direction(1, 0) {}

    void update()
    {
        if (type == Police)
        {
            moveAuto();
            std::cout << "Police" << std::endl;
        }
        else if(type == Thief)
        {
            moveManual();
            std::cout << "Theif" << std::endl;

        }
    }

    void draw(sf::RenderWindow &window)
    {
        sf::CircleShape shape(10);
        shape.setPosition(position);
        shape.setFillColor(type == Police ? sf::Color::Blue : sf::Color::Red);
        window.draw(shape);
    }
    // set speed
    void setSpeed(float speed)
    {
        this->speed = speed;
    }

private:
    Type type;
    MoveType moveType;
    float speed;
    sf::Vector2f position;
    sf::Vector2f direction;

    void moveAuto()
    {
        position += direction * speed;

        if (position.x >= 300 || position.x <= 0)
        {
            direction.x = -direction.x;
        }
        if (position.y >= 300 || position.y <= 0)
        {
            direction.y = -direction.y;
        }
    }

    void moveManual()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (position.y >= speed)
                position.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (position.y <= 300 - speed)
                position.y += speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (position.x >= speed)
                position.x -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (position.x <= 300 - speed)
                position.x += speed;
        }
    }
};