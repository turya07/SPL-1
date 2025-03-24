class LoadImage
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int playerId;

public:
    LoadImage();
    LoadImage(const std::string &imagePath, int playerId);
    void draw(sf::RenderWindow &);
    void move(sf::Vector2f);
    ~LoadImage();
};
LoadImage::LoadImage(){
    
}
LoadImage::LoadImage(const std::string &imagePath, int playerId) : playerId(playerId)
{
    if (!texture.loadFromFile(imagePath))
        std::cerr << "Failed to Create Texture from Image" << std::endl;
    else
    {
        std::cout << "Successfully Created Player Texture, PID: " + std::to_string(playerId) << std::endl;
        sprite = sf::Sprite();
        sprite.setTexture(texture);
        sprite.setOrigin({0, 0});
        sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        // sprite.setScale(BLOCK_SIZE / texture.getSize().x, BLOCK_SIZE / texture.getSize().y);
    }
}

void LoadImage::move(sf::Vector2f pos)
{
    sprite.move(pos);
}

void LoadImage::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

LoadImage::~LoadImage()
{
}