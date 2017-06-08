#ifndef TERRAIN_HPP
# define TERRAIN_HPP

#include "Vect.hpp"

class Fixture;

class Terrain
{
public:
  struct Tile
  {
    bool isSolid;
  };
  
private:  
  Tile tiles[100][100];
  
  constexpr Tile &getTile(Vect<2u, unsigned int> pos)
  {
    return tiles[pos[0]][pos[1]];
  }
public:

  constexpr Terrain()
  : tiles()
  {
    for (Vect<2u, unsigned int> i(0, 0); i[1] != getSize()[1]; ++i[1])
      for (i[0]  = 0u; i[0] != getSize()[0]; ++i[0])
	getTile(i) = {!(rand() & 7) || !i[0] || !i[0]};
  }

  constexpr Vect<2u, unsigned int> getSize() const
  {
    return {100, 100};
  }

  constexpr Tile const &getTile(Vect<2u, unsigned int> pos) const
  {
    if (pos[0] >= 100 || pos[1] >= 100)
      return tiles[0][0];
    return tiles[pos[0]][pos[1]];
  }

  constexpr void correctFixture(Fixture &fixture);
};

#include "Fixture.hpp"

constexpr void Terrain::correctFixture(Fixture &fixture)
{
  Vect<2u, Vect<2u, double>> const extremes{(fixture.pos - Vect<2u, double>{fixture.radius, fixture.radius}),
      (fixture.pos + Vect<2u, double>{fixture.radius, fixture.radius})};
  Vect<2u, Vect<2u, unsigned>> const roundedExtremes(extremes);
  Vect<2u, unsigned> const roundedCenter(fixture.pos);

  { // Test sides. TODO: find a way to avoid code duplication without loosing clarity.
    if (getTile({roundedExtremes[0][0], roundedCenter[1]}).isSolid)
      fixture.pos[0] = (roundedExtremes[0][0] + 1) + fixture.radius;
    else if (getTile({roundedExtremes[1][0], roundedCenter[1]}).isSolid)
      fixture.pos[0] = roundedExtremes[1][0] - fixture.radius;
    if (getTile({roundedCenter[0], roundedExtremes[0][1]}).isSolid)
      fixture.pos[1] = (roundedExtremes[0][1] + 1) + fixture.radius;
    else if (getTile({roundedCenter[0], roundedExtremes[1][1]}).isSolid)
      fixture.pos[1] = roundedExtremes[1][1] - fixture.radius;
  }
  {
    Vect<2u, unsigned> i{};

    for (unsigned int k : {0, 1})
      for (unsigned int j : {0, 1})
	{
	  for (i[1] = roundedExtremes[k][1]; i[1] != roundedCenter[1]; i[1] += (1 - 2 * k))
	    for (i[0] = roundedExtremes[j][0]; i[0] != roundedCenter[0]; i[0] += (1 - 2 * j))
	    {
	      Vect<2u, double> corner(i + Vect<2, double>{1 - j, 1 - k});
	      Vect<2u, double> diff(fixture.pos - corner);

	      if (diff.length2() < fixture.radius * fixture.radius && getTile(i).isSolid)
		fixture.pos = corner + diff.normalized() * (fixture.radius);
	    }
	}
  }
}
#endif
