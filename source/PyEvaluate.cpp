#include <algorithm>
#include "PyEvaluate.hpp"

PyEvaluate::PyEvaluate(std::vector<Player> &players,
    std::vector<Enemy> &enemies, Terrain &terrain)
: players(players), enemies(enemies), terrain(terrain)
{
}

Vect<2u, double> PyEvaluate::closestPlayer(Vect<2u, double> pos) const
{
  auto it (std::min_element(players.begin(), players.end(),
    [pos](Player const &a, Player const &b)
      {
        return ((pos - a.pos).length2() < (pos - b.pos).length2() && (pos - a.pos).length2() != 0);
      }));

  return (it == players.end() ? pos : (*it).pos);
}

Vect<2u, double> PyEvaluate::closestEnemy(Vect<2u, double> pos) const
{
  auto it (std::min_element(enemies.begin(), enemies.end(),
    [pos](Enemy const &a, Enemy const &b)
      {
        return ((pos - a.pos).length2() < (pos - b.pos).length2() && (pos - a.pos).length2() != 0);
    }));

  return (it == enemies.end() ? pos : (*it).pos);
}

Vect<2u, double> PyEvaluate::furtherPlayer(Vect<2u, double> pos) const
{
  auto it (std::max_element(players.begin(), players.end(),
    [pos](Player const &a, Player const &b)
      {
        return ((pos - a.pos).length2() < (pos - b.pos).length2() && (pos - a.pos).length2() != 0);
      }));

  return (it == players.end() ? pos : (*it).pos);
}

Vect<2u, double> PyEvaluate::followRightWall(Vect<2u, double> pos) const
{
  bool walls[9];
  bool table[4];

  for (int i(0), j(0); j < 3; i++)
  {
    walls[i + 3 * j] = terrain.getTile(pos +
        Vect<2u, double>{static_cast<double>(i - 1), static_cast<double>(j - 1)}).isSolid;
    if (i == 2)
    {
        i = -1;
        j += 1;
    }
  }
  if ((table[0] = (walls[5] && !walls[7])) ||
      (table[1] = (walls[7] && !walls[3])) ||
      (walls[3] && !walls[1]))
  {
    if (table[0])
      return (pos + Vect<2u, double>{0.0, 1.0});
    else if (table[1])
      return (pos + Vect<2u, double>{-1.0, 0.0});
    else
      return (pos + Vect<2u, double>{0.0, -1.0});
  }
  else if ((table[2] = (walls[1] && !walls[5])) ||
           (table[3] = (walls[2] && !walls[5])) ||
           (walls[8] && !walls[7]))
  {
    if (table[2])
      return (pos + Vect<2u, double>{1.0, 0.0});
    else if (table[3])
      return (pos + Vect<2u, double>{1.0, 0.0});
    else
      return (pos + Vect<2u, double>{0.0, 1.0});
  }
  else
  {
    if (walls[6] && !walls[3])
      return (pos + Vect<2u, double>{-1.0, 0.0});
    else if (walls[0] && !walls[1])
      return (pos + Vect<2u, double>{0.0, -1.0});
    else
      return (pos + Vect<2u, double>{1.0, 0.0});
  }
}
