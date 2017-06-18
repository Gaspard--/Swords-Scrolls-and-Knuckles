#include <random>
#include <algorithm>
#include "Terrain.hpp"

void Terrain::generateLevel(unsigned int seed)
{
  this->seed = seed;
  for (Vect<2u, unsigned int> i(0u, 0u); i[1] != getSize()[1]; ++i[1])
    for (i[0]  = 0u; i[0] != getSize()[0]; ++i[0])
      getTile(i) = {true};
  
  std::minstd_rand engine(seed);
  std::uniform_int_distribution<> rangeX(10, getSize()[0] - 10);
  std::uniform_int_distribution<> rangeY(10, getSize()[1] - 12);
  std::uniform_int_distribution<> range10(5, 10);
  std::uniform_int_distribution<> range5(0, 4);
  std::vector<Vect<2u, unsigned int>> rooms;

  for (unsigned int i(0); i < 30; ++i)
    rooms.emplace_back(static_cast<unsigned int>(rangeX(engine)), static_cast<unsigned int>(rangeY(engine)));
  std::vector<Vect<2u, unsigned int>> startNodes{};

  rooms.emplace_back(10u, 10u);
  rooms.emplace_back(getSize()[0] - 10u, getSize()[0] - 10u);
  startNodes.emplace_back(getSize()[0] / 2u, getSize()[1] / 2u);
  for (auto &&roomPos : rooms)
    {
      bool genConnection(true);

      Vect<2u, unsigned int> size(static_cast<unsigned int>((range10(engine) + range10(engine)) / 2), static_cast<unsigned int>((range10(engine) + range10(engine)) / 2));
      Vect<2u, unsigned int> relative(static_cast<unsigned int>(range5(engine)), static_cast<unsigned int>(range5(engine)));

      for (Vect<2u, unsigned int> i(0u, 0u); i[1] != size[1]; ++i[1])
	for (i[0] = 0u; i[0] != size[0]; ++i[0])
	  {
	    genConnection = genConnection && getTile(i + roomPos - relative).isSolid;
	    getTile(i + roomPos - relative) = {false};
	  }
      if (genConnection)
      	{
	  Vect<2u, unsigned int> start(*std::min_element(startNodes.begin(), startNodes.end(),
							 [roomPos](auto const &a, auto const &b)
							 {
							   return (roomPos - a).length2() < (roomPos - b).length2();
							 }));
	  unsigned int firstDir(std::uniform_int_distribution<>(0, 1)(engine));
	  unsigned int width(std::uniform_int_distribution<>(1, 2)(engine));

	  for (unsigned int k : {firstDir, 1 - firstDir})
	    {
	      while (start[k] != roomPos[k])
	      	{
		  for (Vect<2u, unsigned int> l(0u, 0u); l[1 - k] != width; ++l[1 - k])
		    getTile(start + l) = {false};
		  start[k] += (start[k] < roomPos[k]) - (start[k] > roomPos[k]);
		}
	    }
	}      
    }
}
