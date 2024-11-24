#include <SFML/Graphics.hpp>
class Dot {
public:
    sf::CircleShape shape;

    Dot(float x, float y, float radius, sf::Color color) {
        shape.setPosition(x, y);
        shape.setRadius(radius);
        shape.setFillColor(color);
        position = shape.getPosition();
        this->radius = radius;
        this->color = color;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
    void updatePosition(float x, float y) {
        shape.move(x, y);
        position = shape.getPosition();
    }
    sf::Vector2 <float> getPosition() {
        return position;
    }
    bool checkTouched(sf::CircleShape& shape) {
        return this->shape.getGlobalBounds().intersects(shape.getGlobalBounds());
    }
private:
    sf::Vector2f position;
    float radius;
    sf::Color color;
};