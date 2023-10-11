#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (TTF_Init() < 0) {
    std::cerr << "TTF could not initialize.\n";
    std::cerr << "TTF_Error: " << TTF_GetError();
  }

  titleFont = TTF_OpenFont("../resources/Tuffy_Bold.ttf", 60);
  promptFont = TTF_OpenFont("../resources/Tuffy_Bold.ttf", 30);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  TTF_CloseFont(titleFont);
  TTF_CloseFont(promptFont);
  TTF_Quit();
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, Walls &walls) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // //Render walls
  SDL_SetRenderDrawColor(sdl_renderer, 126, 0, 251, 255);
  for (SDL_Rect rect: walls.GetWalls()) {
    SDL_RenderFillRect(sdl_renderer, &rect);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::StartScreen()
{
  SDL_Surface * titleSurface = TTF_RenderText_Solid(titleFont, "SNAKE", titleColor);
  SDL_Surface * promptSurface = TTF_RenderText_Solid(promptFont, "Press any key to play..", titleColor);

  SDL_Texture * titleTexture = SDL_CreateTextureFromSurface(sdl_renderer, titleSurface);
  SDL_Texture * promptTexture = SDL_CreateTextureFromSurface(sdl_renderer, promptSurface);
  
  int titleW = 0, titleH = 0, promptW = 0, promptH = 0;

  SDL_QueryTexture(titleTexture, NULL, NULL, &titleW, &titleH);
  SDL_QueryTexture(promptTexture, NULL, NULL, &promptW, &promptH);

  int titleX = (screen_width - titleW) / 2;
  int titleY = (screen_height - titleH) / 3;
  int promptX = (screen_width - promptW) / 2;
  int promptY = (screen_height - promptH) / 2;

  SDL_Rect titleRect = {titleX, titleY, titleW, titleH};
  SDL_Rect promptRect = {promptX, promptY, promptW, promptH};

  SDL_RenderCopy(sdl_renderer, titleTexture, NULL, &titleRect);
  SDL_RenderCopy(sdl_renderer, promptTexture, NULL, &promptRect);

  SDL_RenderPresent(sdl_renderer);

  SDL_DestroyTexture(titleTexture);
  SDL_DestroyTexture(promptTexture);
  SDL_FreeSurface(titleSurface);
  SDL_FreeSurface(promptSurface);
}

void Renderer::LevelUp()
{
  SDL_Surface * levelSurface = TTF_RenderText_Solid(titleFont, "LEVEL UP", titleColor);
  SDL_Texture * levelTexture = SDL_CreateTextureFromSurface(sdl_renderer, levelSurface);

  int levelW = 0, levelH = 0;

  SDL_QueryTexture(levelTexture, NULL, NULL, &levelW, &levelH);

  int levelX = (screen_width - levelW) / 2;
  int levelY = (screen_height - levelH) / 2;

  SDL_Rect levelRect = {levelX, levelY, levelW, levelH};

  SDL_RenderCopy(sdl_renderer, levelTexture, NULL, &levelRect);
  SDL_RenderPresent(sdl_renderer);

  SDL_Delay(2000);

  SDL_DestroyTexture(levelTexture);
  SDL_FreeSurface(levelSurface);
}

void Renderer::UpdateWindowTitle(int score, int fps, int level) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " Level: " + std::to_string(level)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
