#ifndef PYEVALUATE_HPP_
# define PYEVALUATE_HPP_

#include <vector>
#include "Player.hpp"

struct PyEvaluate
{
  PyEvaluate(std::vector<Player> &);
  ~PyEvaluate() = default;

  Vect<2u, double> closestPlayer(Vect<2u, double> pos) const;
  //Vect<2u, double> closestEnemy(Vect<2u, double> pos) const;

  std::vector<Player> &players;
};

#endif // !PYEVALUATE_HPP_
