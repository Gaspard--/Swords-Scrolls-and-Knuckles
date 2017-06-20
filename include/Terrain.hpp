#ifndef TERRAIN_HPP
# define TERRAIN_HPP

#include "Vect.hpp"
#include "Util.hpp"

class Terrain
{
public:
  struct Tile
  {
    bool isSolid;
    unsigned int roomId;
  };

  struct Room
  {
    Vect<2, double> pos;
    unsigned int id;
    bool mobsSpawned;

    constexpr Room(Vect<2u, double> pos, unsigned int id = 0, bool mobsSpawned = true)
    : pos(pos)
      , id(id)
      , mobsSpawned(mobsSpawned)
    {}
  };
private:  
  Tile tiles[100][100];
  std::vector<Room> rooms;
  unsigned int seed;

public:

  Terrain();

  void generateLevel(unsigned int seed);
  
  Vect<2u, unsigned int> getSize() const;
  
  Room &getRoom(Vect<2u, unsigned int> pos);

  Tile const &getTile(Vect<2u, unsigned int> pos) const;

  Tile &getTile(Vect<2u, unsigned int> pos);

  template<class RESPONSE, class FIXTURE>
  void correctFixture(FIXTURE &fixture, RESPONSE &&response)
  {
    if (!fixture.doTerrainCollision())
      return ;
    Vect<2u, Vect<2u, double>> const extremes{(fixture.pos - Vect<2u, double>{fixture.radius, fixture.radius}),
	(fixture.pos + Vect<2u, double>{fixture.radius, fixture.radius})};
    Vect<2u, Vect<2u, unsigned>> const roundedExtremes(extremes);
    Vect<2u, unsigned> const roundedCenter(fixture.pos);

    { // Test sides. TODO: find a way to avoid code duplication without loosing clarity.
      if (getTile({roundedExtremes[0][0], roundedCenter[1]}).isSolid)
	{
	  fixture.pos[0] = (roundedExtremes[0][0] + 1) + fixture.radius;
	  response(fixture, Vect<2u, double>{1.0, 0.0});
	}
      else if (getTile({roundedExtremes[1][0], roundedCenter[1]}).isSolid)
	{
	  fixture.pos[0] = roundedExtremes[1][0] - fixture.radius;
	  response(fixture, Vect<2u, double>{-1.0, 0.0});
	}
      if (getTile({roundedCenter[0], roundedExtremes[0][1]}).isSolid)
	{
	  fixture.pos[1] = (roundedExtremes[0][1] + 1) + fixture.radius;
	  response(fixture, Vect<2u, double>{0.0, 1.0});
	}
      else if (getTile({roundedCenter[0], roundedExtremes[1][1]}).isSolid)
	{
	  fixture.pos[1] = roundedExtremes[1][1] - fixture.radius;
	  response(fixture, Vect<2u, double>{0.0, -1.0});
	}
    }
    {
      for (unsigned int k : {0, 1})
	for (unsigned int j : {0, 1})
	  {
	    Vect<2u, unsigned> i{};

	    for (i[1] = roundedExtremes[k][1]; i[1] != roundedCenter[1]; i[1] += (1 - 2 * k))
	      for (i[0] = roundedExtremes[j][0]; i[0] != roundedCenter[0]; i[0] += (1 - 2 * j))
		{
		  Vect<2u, double> const corner(i + Vect<2, unsigned>{1 - j, 1 - k});
		  Vect<2u, double> const diff(fixture.pos - corner);
		  Vect<2u, double> const normalizedDiff(diff.normalized());

		  if (diff.length2() < fixture.radius * fixture.radius && getTile(i).isSolid)
		    {
		      fixture.pos = corner + normalizedDiff * fixture.radius;
		      response(fixture, -normalizedDiff);
		    }
		}
	  }
    }
  }


  template<class FIXTURE>
  void correctFixture(FIXTURE &fixture)
  {
    return correctFixture(fixture, NOOP{});
  }
};

#endif
