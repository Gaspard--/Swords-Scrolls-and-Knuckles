#ifndef GAME_STATE_HPP
# define GAME_STATE_HPP

#include <vector>
#include "Terrain.hpp"

class Player;
class Enemy;
class Projectile;

struct GameState
{
  Terrain terrain;
  std::vector<Player> players;
  std::vector<Enemy> enemies;
  std::vector<Projectile> projectiles;
};

#endif
