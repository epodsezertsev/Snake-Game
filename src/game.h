#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "wall.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int GetLevel() const;
  void LevelUp(Renderer &renderer);

 private:
  Snake snake;
  Walls walls;
  SDL_Point food;
  bool running{false};
  bool start {false};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int level{1};

  void PlaceFood();
  void Update(Renderer &renderer);
};

#endif