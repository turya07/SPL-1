#ifndef HEADER_HPP
#define HEADER_HPP


// built-in c++ lib
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <thread>

// CONST COLOR
#define TRANSPARENT sf::Color::Transparent
#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define RED sf::Color::Red
#define BLUE sf::Color::Blue
#define CYAN sf::Color::Cyan
#define YELLOW sf::Color::Yellow
#define GREEN sf::Color::Green

// CONST SIZE
#define BOX_DIMENSION (int)912
#define WIDTH BOX_DIMENSION
#define HEIGHT BOX_DIMENSION * 3 / 4
#define BLOCK_SIZE (int)16
#define GAP (int)20

// graphics lib
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
// local lib from client
#include "Block.hpp"
#include "Person.hpp"
#include "TimeBox.hpp"
#include "Server.hpp" // server lib

#endif // HEADER_HPP