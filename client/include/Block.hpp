#define UP sf::Keyboard::W
#define DOWN sf::Keyboard::S
#define LEFT sf::Keyboard::A
#define RIGHT sf::Keyboard::D
#define SP sf::Keyboard::Space

typedef struct ID
{
    int idx;
    int idy;
} ID;

class Block
{
public:
    Block(int width, float x, float y);
    Block(int width, float x, float y, ID id);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void deleteIt();
    bool isColliding();
    void move(sf::Event ev, sf::Vector2f startBoundary, sf::Vector2f endBoundary, std::vector<std::vector<Block>> blocks);
    void setPosition(sf::Vector2f position);
    void setColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setOutlineThickness(float thickness);
private:
    int width;
    int height;
    int speed = 10;
    ID id = {0, 0};
    sf::Vector2f position;
    sf::RectangleShape block;
    sf::Color myColor;
};

Block::Block(int width, float x, float y)
{
    this->width = width;
    this->height = width;
    block.setSize(sf::Vector2f(width, width));
    block.setPosition(x, y);
    block.setFillColor(sf::Color::White);
    myColor = sf::Color::White;
    block.setOutlineColor(sf::Color::Black);
    block.setOutlineThickness(1);
    speed = width;
}
Block::Block(int width, float x, float y, ID id)
{
    this->width = width;
    this->height = width;
    block.setSize(sf::Vector2f(width, width));
    block.setPosition(x, y);
    block.setFillColor(sf::Color::White);
    myColor = sf::Color::White;
    block.setOutlineColor(sf::Color::Black);
    block.setOutlineThickness(1);
    speed = width;
    this->id = {id.idx, id.idy};
}

void Block::draw(sf::RenderWindow &window)
{
    window.draw(block);
}

sf::Vector2f Block::getPosition()
{
    return block.getPosition();
}

sf::Vector2f Block::getSize()
{
    return block.getSize();
}
void Block::deleteIt()
{
    block.setSize(sf::Vector2f(0, 0));
    block.setFillColor(sf::Color::Transparent);
    block.setOutlineColor(sf::Color::Transparent);
    myColor = sf::Color::Transparent;
}

bool Block::isColliding()
{
    return sf::Color::Transparent != myColor;
}

void Block::move(sf::Event ev, sf::Vector2f startBoundary, sf::Vector2f endBoundary, std::vector<std::vector<Block>> blocks)
{
    // need more optimization to avoid collision with blocks
    if (ev.key.code == UP && block.getPosition().y > startBoundary.y + height)
    {
        for (auto i : blocks)
        {
            for (auto j : i)
            {
                if (j.getPosition().x == block.getPosition().x && block.getPosition().y - speed == j.getPosition().y)
                {
                    if (j.isColliding())
                    {
                        return;
                    }
                }
            }
        }
        block.move(0, -speed);
    }
    else if (ev.key.code == DOWN && block.getPosition().y < endBoundary.y - height)
    {
        for (auto i : blocks)
        {
            for (auto j : i)
            {
                if (j.getPosition().x == block.getPosition().x && block.getPosition().y + speed == j.getPosition().y)
                {
                    if (j.isColliding())
                    {
                        return;
                    }
                }
            }
        }
        block.move(0, speed);
    }
    else if (ev.key.code == LEFT && block.getPosition().x > startBoundary.x + width)
    {
        for (auto i : blocks)
        {
            for (auto j : i)
            {
                if (j.getPosition().x == block.getPosition().x - speed && block.getPosition().y == j.getPosition().y)
                {
                    if (j.isColliding())
                    {
                        return;
                    }
                }
            }
        }
        block.move(-speed, 0);
    }
    else if (ev.key.code == RIGHT && block.getPosition().x < endBoundary.x - width)
    {
        for (auto i : blocks)
        {
            for (auto j : i)
            {
                if (j.getPosition().x == block.getPosition().x + speed && block.getPosition().y == j.getPosition().y)
                {
                    if (j.isColliding())
                    {
                        return;
                    }
                }
            }
        }
        block.move(speed, 0);
    }
}

void Block::setPosition(sf::Vector2f position)
{
    block.setPosition(position);
}

void Block::setColor(sf::Color color)
{
    block.setFillColor(color);
    myColor = color;
}
void Block::setOutlineColor(sf::Color color)
{
    block.setOutlineColor(color);
}

void Block::setOutlineThickness(float thickness)
{
    block.setOutlineThickness(thickness);
}
