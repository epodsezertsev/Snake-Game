#include "game.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;
  while (!start) {
    controller.HandleInput(start, running);
    renderer.StartScreen();
  }
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update(renderer);
    renderer.Render(snake, food, walls);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, level);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Creating an SDL point to test against the walls.
    SDL_Point testing_cell{
      static_cast<int>(x * 20),
      static_cast<int>(y * 20)};
    // Check that the location is not occupied by a snake item or a wall before placing
    // food.
    if (!snake.SnakeCell(x, y) && !walls.IsWall(testing_cell)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update(Renderer &renderer) {
  SDL_Point testing_cell{
    static_cast<int>(snake.head_x * 20),
    static_cast<int>(snake.head_y * 20)};
  if (walls.CheckCollision(testing_cell)){
    snake.alive = false;
  }
  if (!snake.alive) {
    sleep(2);
    running = false;
    std::cout << "Game Over :(\n";
    return;
  }
  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    if (score == 3){
      LevelUp(renderer);
    } else {
      snake.GrowBody();
      snake.speed += 0.02;
    }
  }
}

void Game::LevelUp(Renderer &renderer)
{
  //This function will be called when the snake size increases to 15.
  //I'll need to render a level up screen
  //RenderScreen here;
  level++;
  if (level == 6){
    running = false;
    level = 5;//terminates the game and sets the level to 5 so it prints correctly.
    std::cout << "GAME WON!!!\n";
  } else (
    renderer.LevelUp();
  )
  walls.UpdateLevel(level);
  snake.UpdateLevel();
  score = 0;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetLevel() const { return level; }