#include <algorithm>
#include "PyEvaluate.hpp"

PyEvaluate::PyEvaluate(std::vector<Player> &players, std::vector<Enemy> &enemies)
: players(players), enemies(enemies)
{
}

Vect<2u, double> PyEvaluate::closestPlayer(Vect<2u, double> pos) const
{
  return ((*std::min_element(players.begin(), players.end(),
    [pos](Player const &a, Player const &b)
      {
        return ((pos - a.pos).length2() < (pos - b.pos).length2() && (pos - a.pos).length2() != 0);
      })).pos);
}

Vect<2u, double> PyEvaluate::closestEnemy(Vect<2u, double> pos) const
{
  return ((*std::min_element(enemies.begin(), enemies.end(),
    [pos](Enemy const &a, Enemy const &b)
      {
        return ((pos - a.pos).length2() < (pos - b.pos).length2() && (pos - a.pos).length2() != 0);
      })).pos);
}
