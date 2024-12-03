# Project-Title: Escape the Cops

<big>At the beginning of the game, a thief will stand at the center of the window. 3 policies will be on three corners of the window. Now the user/player has to control the thief so that the policies can not catch him. There are different levels of difficulty. 3 Policies have different types of speed.

The game will have three levels.
-  Easy
-  Medium
-  Hard


User has to choose any level. Depending on the selected level, there will be some obstacles in random positions so that the thief can hide from cops. The cops know in which direction the thief is but not the exact position. So they will traverse  through the path. There will be a timer that will be the score of the game. All the scores will be stored in a single file but the top five and current game score will be shown in the Game UI.
</big>


## Table of Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Requirements

* Language: `C` & `C++`
* Graphics-Tools: `SFML`
* Algorithms:  `DP`, `BFS`, `GREEDY`


## Installation

- Install build-essential for GCC & G++
```
sudo apt install build-essential
```
- install SFML
```
sudo apt-get install libsfml-dev
```
**If you encounter any problem to install any of the packages, then first type the code below and then try the process again.**
```
sudo apt update && sudo apt-get update
```

## Usage
* To compile c++ file:

```
g++ -c main.cpp
```
* To create executable file:

```
g++ -o game main.o -lsfml-graphics -lsfml-window -lsfml-system
```
* To run the **END-USER** app/game:

```
./game
```

## Contributing

Guidelines for contributing to the project.

## License

Free for all for practice

## Contact

- Name: *TURYA BISWAS*
- Roll: *1507*
- E-mail: <a href="mailto:bsse1507@iit.du.ac.bd">bsse1507@iit.du.ac.bd</a>