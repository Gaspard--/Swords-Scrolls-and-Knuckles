#ifndef PYEVALUATE_HPP_
# define PYEVALUATE_HPP_

#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Terrain.hpp"

struct PyEvaluate
{
  PyEvaluate(std::vector<Player> &, std::vector<Enemy> &, Terrain &terrain);
  ~PyEvaluate() = default;

  Vect<2u, double> closestPlayer(Vect<2u, double> pos) const;
  Vect<2u, double> furtherPlayer(Vect<2u, double> pos) const;
  Vect<2u, double> closestEnemy(Vect<2u, double> pos) const;
  Vect<2u, double> followRightWall(Vect<2u, double> pos) const;

  std::vector<Player> &players;
  std::vector<Enemy> &enemies;
  Terrain &terrain;
};

#endif // !PYEVALUATE_HPP_
