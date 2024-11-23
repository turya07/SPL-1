#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Game
{
public:
    Game(sf::RenderWindow &window);
    void run();
    void handleEvents();
    void goLeft();
    void goRight();

private:
    void reFactorShape(float x);

    // rendered windows
    sf::RenderWindow &window;
    // text and font
    sf::Text text;
    sf::Font font;
    std::vector<sf::Color> colors;
    // shape & it's position
    sf::Vector2f position;
    sf::CircleShape shape;
    // key / mouse event
    sf::Event event;
    float const radius = 25.f;
    int colorIndex;
};