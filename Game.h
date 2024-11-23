
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(sf::RenderWindow &window) : window(window)
    {
        shape.setRadius(100.f);
        colors = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};
        colorIndex = 0;
    }
    void reFactorShape(float x)
    {
        shape.setRadius(x);
    }
    void run()
    {
        sf::Clock clock;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            if (clock.getElapsedTime().asSeconds() >= 1.0f)
            {
                clock.restart();
                reFactorShape(10.f + colorIndex * 5.f);
                colorIndex = (colorIndex + 1) % colors.size();
                shape.setFillColor(colors[colorIndex]);
            }

            window.clear();
            window.draw(shape);
            window.display();
        }
    }

private:
    sf::RenderWindow &window;
    sf::CircleShape shape;
    std::vector<sf::Color> colors;
    int colorIndex;
};