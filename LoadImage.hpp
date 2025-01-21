#include <SFML/Graphics.hpp>
#include <iostream>
class LoadImage
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    LoadImage(/* args */);
    void draw(sf::RenderWindow &);
    ~LoadImage();
};

LoadImage::LoadImage()
{
    if (!texture.loadFromFile("./assets/bg.jpg"))
        std::cerr << "Failed to Load Image Texture" << std::endl;
    else
    {
        sprite = sf::Sprite(texture);
        sprite.setOrigin({20 * 5, 20 * 20 + 100});
    }
}
void LoadImage::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}
LoadImage::~LoadImage()
{
}
