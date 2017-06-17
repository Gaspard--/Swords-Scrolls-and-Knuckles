#include <random>
#include "Terrain.hpp"

void Terrain::generateLevel(unsigned int seed)
{
  this->seed = seed;
  for (Vect<2u, unsigned int> i(0u, 0u); i[1] != getSize()[1]; ++i[1])
    for (i[0]  = 0u; i[0] != getSize()[0]; ++i[0])
      getTile(i) = {true};
  
  std::minstd_rand engine(seed);
  std::uniform_int_distribution<> rangeX(10, getSize()[0] - 10);
  std::uniform_int_distribution<> rangeY(10, getSize()[1] - 10);
  std::uniform_int_distribution<> range10(6, 10);
  std::uniform_int_distribution<> range5(0, 5);
  std::vector<Vect<2u, unsigned int>> rooms;

  for (unsigned int i(0); i < 50; ++i)
    rooms.emplace_back(rangeX(engine), rangeX(engine));
  std::vector<Vect<2u, unsigned int>> startNodes{};

  rooms.emplace_back(10u, 10u);
  rooms.emplace_back(getSize()[0] - 10u, getSize()[0] - 10u);
  startNodes.emplace_back(getSize()[0] - 10u, getSize()[0] - 10u);
  for (auto &&roomPos : rooms)
    {
      bool genConnection(true);

      Vect<2u, unsigned int> size(range10(engine), range10(engine));
      Vect<2u, unsigned int> relative(range5(engine), range5(engine));

      for (Vect<2u, unsigned int> i(0u, 0u); i[1] != size[1]; ++i[1])
	for (i[0] = 0u; i[0] != size[0]; ++i[0])
	  {
	    genConnection = genConnection && getTile(i + roomPos - relative).isSolid;
	    getTile(i + roomPos - relative) = {false};
	  }
      if (genConnection)
	{
	  Vect<2u, unsigned int> start(startNodes.back());
	  unsigned int firstDir(std::uniform_int_distribution<>(0, 1)(engine));

	  for (unsigned int k : {firstDir, 1 - firstDir})
	    {
	      while (start[k] != roomPos[k])
		{
		  getTile(start) = {false};
		  start[k] += (start[k] < roomPos[k]) * 2u - 1u;
		}
	    }
	}
      
    }
}
