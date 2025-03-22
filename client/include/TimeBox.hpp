class TimeBox
{
public:
    TimeBox()
    {
    }
    TimeBox(sf::Font &font, sf::Color col, unsigned int dimension, int y_axis)
    {
        timerBox.setFont(font);
        timerBox.setCharacterSize(16);
        timerBox.setFillColor(col);
        timerBox.setPosition(dimension - 16 * 16, y_axis);
    }
    void draw(sf::RenderWindow &window, int time)
    {
        timerBox.setString("Time Elapsed: " + std::to_string(time) + "s");
        window.draw(timerBox);
    }
    ~TimeBox() {};

private:
    sf::Text timerBox;
};