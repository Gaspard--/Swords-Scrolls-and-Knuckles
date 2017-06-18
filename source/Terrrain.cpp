#include <random>
#include <algorithm>
#include "Terrain.hpp"

Terrain::Terrain()
  : tiles{}
  , seed(0u)
{}

Vect<2u, unsigned int> Terrain::getSize() const
{
  return {100u, 100u};
}

Terrain::Room &Terrain::getRoom(Vect<2u, unsigned int> pos)
{
  return rooms[getTile(pos).roomId];
}

Terrain::Tile const &Terrain::getTile(Vect<2u, unsigned int> pos) const
{
  if (pos[0] >= getSize()[0] || pos[1] >= getSize()[1])
    return tiles[0][0];
  return tiles[pos[0]][pos[1]];
}

Terrain::Tile &Terrain::getTile(Vect<2u, unsigned int> pos)
{
  if (pos[0] >= getSize()[0] || pos[1] >= getSize()[1])
    return tiles[0][0];
  return tiles[pos[0]][pos[1]];
}

void Terrain::generateLevel(unsigned int seed)
{
  this->seed = seed;
  for (Vect<2u, unsigned int> i(0u, 0u); i[1] != getSize()[1]; ++i[1])
    for (i[0]  = 0u; i[0] != getSize()[0]; ++i[0])
      getTile(i) = {true, 0u};

  std::minstd_rand engine(seed);
  std::uniform_int_distribution<> rangeX(10, getSize()[0] - 10);
  std::uniform_int_distribution<> rangeY(10, getSize()[1] - 12);
  std::uniform_int_distribution<> range10(5, 10);
  std::uniform_int_distribution<> range5(1, 4);
  // std::vector<Vect<2u, unsigned int>> rooms;

  rooms.emplace_back(Vect<2u, unsigned int>{10u, 10u});
  for (unsigned int i(1); i < 30; ++i)
    rooms.emplace_back(Vect<2u, unsigned int>{rangeX(engine), rangeY(engine)}, i, false);
  rooms.emplace_back(getSize() - Vect<2u, unsigned int>{5u, 5u}, 30u, false);
  std::vector<Vect<2u, unsigned int>> startNodes{};

  startNodes.emplace_back(getSize()[0] / 2u, getSize()[1] / 2u);
  for (auto &&room : rooms)
    {
      bool genConnection(true);

      Vect<2u, unsigned int> size((range10(engine) + range10(engine)) / 2u, (range10(engine) + range10(engine)) / 2u);
      Vect<2u, unsigned int> relative(range5(engine), range5(engine));

      for (Vect<2u, unsigned int> i(0u, 0u); i[1] != size[1]; ++i[1])
	for (i[0] = 0u; i[0] != size[0]; ++i[0])
	  {
	    genConnection = genConnection && getTile(i + room.pos - relative).isSolid;
	    getTile(i + room.pos - relative) = {false, room.id};
	  }
      if (genConnection)
      	{
	  Vect<2u, unsigned int> start(*std::min_element(startNodes.begin(), startNodes.end(),
							 [room](auto const &a, auto const &b)
							 {
							   return (room.pos - a).length2() < (room.pos - b).length2();
							 }));
	  unsigned int firstDir(std::uniform_int_distribution<>(0, 1)(engine));
	  unsigned int width(std::uniform_int_distribution<>(1, 2)(engine));

	  for (unsigned int k : {firstDir, 1 - firstDir})
	    {
	      while (start[k] != room.pos[k])
	      	{
		  for (Vect<2u, unsigned int> l(0u, 0u); l[1 - k] != width; ++l[1 - k])
		    getTile(start + l) = {false, 0u};
		  start[k] += (start[k] < room.pos[k]) - (start[k] > room.pos[k]);
		}
	    }
	}
    }
}
