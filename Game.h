#include <iostream>
#include <vector>

#include "Dot.h"

class Game
{
public:
    Game(sf::RenderWindow &window);
    void run();
    void handleEvents();

    void createRandomObjects(int, sf::RenderWindow &);
    void drawObjects(sf::RenderWindow &);
    void updateScore();
private:
    void reFactorShape(float x);
    void goLeft();
    void goRight();
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
    int score = 0;
    std::vector<Dot> dots;
};