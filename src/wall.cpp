#include "wall.h"
#include <vector>
#include <iostream>

bool Walls::CheckCollision(SDL_Point &point)
{
  for (auto wall : _walls) {
    if (SDL_PointInRect(&point, &wall) == SDL_TRUE){
        return true;
    }
  }
  return false;
}

void Walls::PopulateVector()
{
  switch (_level) {
    case 1:
      break;
    case 2:
      _walls.emplace_back(wall1);
      break;
    case 3:
      _walls.emplace_back(wall2);
      break;
    case 4:
      _walls.emplace_back(wall3);
      break;
    case 5:
      _walls.emplace_back(wall4);
      break;
  }
}

bool Walls::IsWall(SDL_Point &item)
{
  for (auto wall : _walls) {
    if (SDL_PointInRect(&item, &wall) == SDL_TRUE){
        return true;
    }
  }
  return false;
}

std::vector<SDL_Rect> Walls::GetWalls()
{
    return _walls;
}

void Walls::UpdateLevel(int &level)
{
  _level = level;
  PopulateVector();
}
