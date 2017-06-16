#ifndef GAME_STATE_HPP
# define GAME_STATE_HPP

#include <vector>
#include "Terrain.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"

struct GameState
{
  Terrain terrain;
  std::vector<Player> players;
  std::vector<Enemy> enemies;
  std::vector<Projectile> projectiles;
};

#endif
