#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Function to create a gradient rectangle
sf::VertexArray createGradient(const sf::Vector2f& size, const sf::Color& topColor, const sf::Color& bottomColor) {
    sf::VertexArray gradient(sf::Quads, 4);

    // Top-left corner
    gradient[0].position = sf::Vector2f(0, 0);
    gradient[0].color = topColor;

    // Top-right corner
    gradient[1].position = sf::Vector2f(size.x, 0);
    gradient[1].color = topColor;

    // Bottom-right corner
    gradient[2].position = sf::Vector2f(size.x, size.y);
    gradient[2].color = bottomColor;

    // Bottom-left corner
    gradient[3].position = sf::Vector2f(0, size.y);
    gradient[3].color = bottomColor;

    return gradient;
}

int main() {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu Screen with Gradient", sf::Style::Close);
    window.setFramerateLimit(60);

    // Gradient background colors
    sf::Color topColor(10, 10, 30);   // Dark gray
    sf::Color bottomColor(10, 10, 10); // Almost black

    // Create the gradient background
    sf::VertexArray backgroundGradient = createGradient(sf::Vector2f(window.getSize().x, window.getSize().y), topColor, bottomColor);

    // Font loading
    sf::Font font;
    if (!font.loadFromFile("../client/assets/fonts/firacode.ttf")) { // Replace with your font file path
        std::cerr << "Error: Could not load font!" << std::endl;
        return -1;
    }

    // Menu options
    std::vector<std::string> menuOptions = {"Start Game", "Options", "Exit"};
    std::vector<sf::Text> menuTexts;

    float menuStartY = 200;   // Starting Y position for menu items
    float menuSpacing = 50;   // Spacing between menu items

    for (size_t i = 0; i < menuOptions.size(); ++i) {
        sf::Text text(menuOptions[i], font, 30);
        text.setFillColor(sf::Color(200, 200, 200)); // Light gray text color
        text.setPosition((window.getSize().x - text.getGlobalBounds().width) / 2,
                         menuStartY + i * menuSpacing);
        menuTexts.push_back(text);
    }

    int selectedOptionIndex = 0; // Index of the currently selected menu option

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedOptionIndex = (selectedOptionIndex - 1 + menuOptions.size()) % menuOptions.size();
                } else if (event.key.code == sf::Keyboard::Down) {
                    selectedOptionIndex = (selectedOptionIndex + 1) % menuOptions.size();
                } else if (event.key.code == sf::Keyboard::Enter) {
                    std::cout << "Selected option: " << menuOptions[selectedOptionIndex] << std::endl;
                    if (menuOptions[selectedOptionIndex] == "Exit") {
                        window.close(); // Exit the application
                    }
                }
            }
        }

        // Update menu text colors based on selection
        for (size_t i = 0; i < menuTexts.size(); ++i) {
            if (i == selectedOptionIndex) {
                menuTexts[i].setFillColor(sf::Color(255, 255, 255)); // Highlighted white color
            } else {
                menuTexts[i].setFillColor(sf::Color(200, 200, 200)); // Default light gray color
            }
        }

        // Render everything
        window.clear();
        window.draw(backgroundGradient); // Draw the gradient background

        for (const auto& text : menuTexts) {
            window.draw(text); // Draw each menu option
        }

        window.display();
    }

    return 0;
}