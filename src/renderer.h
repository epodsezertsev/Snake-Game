#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_ttf.h"

#include "snake.h"
#include "wall.h"
//#include "controller.h"


#include <vector>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, Walls &walls);
  void UpdateWindowTitle(int score, int fps, int level);
  void StartScreen();
  void LevelUp();
  void GameWon();
  // void GameOver();

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font* titleFont;
  TTF_Font* promptFont;
  SDL_Color titleColor = {0, 251, 243};

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif