# Project-Title: Escape the Cops

<p>
    <b>
        Name: Turya Biswas
    </b>
</p>
<p>
    <b>
        Roll: 1507
    </b>
</p>
<p>
    <b>
        Superviros: Dr. Md. Nurul Ahad Tawhid
    </b>
</p>
<br />
<p>At the beginning of the game, a thief will stand at the center of the window. 3 policies will be on three corners of the window. Now the user/player has to control the thief so that the policies can not catch him. There are different levels of difficulty. 3 Policies have different types of speed.
</p>

<div>
The game will have three levels.

- Easy
- Medium
- Hard

User has to choose any level. Depending on the selected level, there will be some obstacles in random positions so that the thief can hide from cops. The cops know in which direction the thief is but not the exact position. So they will traverse through the path. There will be a timer that will be the score of the game. All the scores will be stored in a single file but the top five and current game score will be shown in the Game UI.

</div>

## Table of Contents
<div>

- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Acknowledgement](#acknowledgement)
- [Contact](#contact)

</div>

## Requirements
<div>

- Language: `C/C++`
- Graphics-Tools: `SFML`
- Algorithms: `DP`, `BFS`, `GREEDY`
</div>

## Installation
<div>

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
</div>

## Usage
<div>

- To compile c++ file:

```
g++ -c main.cpp
```

- To create executable file:

```
g++ -o game main.o -lsfml-graphics -lsfml-window -lsfml-system
```

- To run the **END-USER** app/game:

```
./game
```

## Tools: Test all c/cpp/header files number of lines
```
./tools/count_lines ./Game.hpp ./Person.hpp ./TimeBox.hpp ./Block.hpp ./bfs.c ./main.cpp ./LoadImage.hpp
```
</div>

## Acknowledgement
<div>

- [SFML Document](https://www.sfml-dev.org/documentation/2.6.2/)
- [SFML Youtube Tutorial](https://www.youtube.com/playlist?list=PLvv0ScY6vfd95GMoMe2zc4ZgGxWYj3vua)

</div>

## Contact

- E-mail: <a href="mailto:bsse1507@iit.du.ac.bd">bsse1507@iit.du.ac.bd</a>
