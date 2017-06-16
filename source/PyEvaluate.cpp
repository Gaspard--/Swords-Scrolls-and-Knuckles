#include <algorithm>
#include "PyEvaluate.hpp"

PyEvaluate::PyEvaluate(std::vector<Player> &players)
: players(players)
{
}

Vect<2u, double> PyEvaluate::closestPlayer(Vect<2u, double> pos) const
{
  return ((*std::min_element(players.begin(), players.end(),
    [pos](Player const &a, Player const &b)
      {
        return ((pos - a.pos).length2() < (pos - b.pos).length2());
      })).pos);
}
