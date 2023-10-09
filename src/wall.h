#ifndef WALL_H
#define WALL_H

#include <vector>
#include "SDL.h"

class Walls {
  public:
    //Walls(int level):_level(level){ PopulateVector(); };
    Walls(){ PopulateVector(); };
    bool CheckCollision(SDL_Point &point);
    bool IsWall(SDL_Point &item);
    void PopulateVector();
    std::vector<SDL_Rect> GetWalls();
    void UpdateLevel(int &level);
  private:
    std::vector<SDL_Rect> _walls;
    int _level = 1;
    SDL_Rect wall1{200, 220, 20, 200};
    SDL_Rect wall2{400, 200, 160, 20};
    SDL_Rect wall3{20, 40, 20, 200};
    SDL_Rect wall4{100, 500, 180, 20};
};


#endif