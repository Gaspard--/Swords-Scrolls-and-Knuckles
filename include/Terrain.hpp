#ifndef TERRAIN_HPP
# define TERRAIN_HPP

#include "Vect.hpp"

class Terrain
{
public:
  struct Tile
  {
    bool isSolid;
  };

  Tile &getTile(Vect<2u, float> pos);
};

#endif
