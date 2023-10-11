# CPPND: Capstone Snake Game Example

This is my Capstone project for the Udacity C++ Nanodegree. The objective of the project was to add features to an existing snake game. The starter repo can be found [here](https://github.com/udacity/CppND-Capstone-Snake-Game).

<img src="snake_game.gif"/>

## Added Features
* SDL rendered start screen - the game does not start until the user presses a button
* Walls class - depending on the level, an obstacle is populated in the game screen. If the snake runs into this obstacle, the game stops.
* Levels - there are 5 levels in the game and a level up screen is rendered between each one.
* SDL rendered end game screen - the original version of the game never shut off. Now there is a screen that pops up when you beat the game or if you hit an obstacle. The game ends automatically after a short delay.

## Rubric Criteria (Must Meet Five)
* The project demonstrates an understanding of C++ functions and control structures.
* The project uses Object Oriented Programming techniques.
* Classes use appropriate access specifiers for class members.
* Classes abstract implementation details from their interfaces.
* Classes encapsulate behavior.
* The project makes use of references in function declarations.
* The project uses destructors appropriately.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2-TTF >= 2.0 (Font Rendering)
  * Linux (Debian Based like Ubuntu): `sudo apt-get install libsdl2-ttf-dev`
  * Windows and Mac OS: the repo link is [here](https://github.com/libsdl-org/SDL_ttf), and an excellent tutorial on how to run it [here](https://www.youtube.com/watch?v=GROeu4fL730&t=325s)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
