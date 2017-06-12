#ifndef PHYSICS_HPP
# define PHYSICS_HPP

#include "Iterators.hpp"
#include "Vect.hpp"

namespace Physics
{

  /**
   * Tests if 2 circles collide, given, their center and radius.
   */
  constexpr bool circleTest(Vect<2u, double> posA, double radiusA,
			    Vect<2u, double> posB, double radiusB)
  {
    return (posB - posA).length2() < (radiusA + radiusB) * (radiusA + radiusB);
  }

  template<class IT_A, class IT_B, class RESPONSE>
  constexpr void collisionTest(IT_A beginA, IT_A endA,
			       IT_B beginB, IT_B endB,
			       RESPONSE &&response)
  {
    for (;beginA != endA; ++beginA)
      for (;beginB != endB; ++beginB)
	if (circleTest(beginA->getPos(), beginA->getRadius(),
		       beginB->getPos(), beginB->getRadius()))
	  response(*beginA, *beginB);
  }

  template<class IT_A, class RESPONSE>
  constexpr void collisionTest(IT_A begin, IT_A end,
			       RESPONSE &&response)
  {
    for (;begin != end; ++begin)
      for (auto begin2(begin); ++begin2 != end;)
	if (circleTest(begin->getPos(), begin->getRadius(),
		       begin2->getPos(), begin2->getRadius()))
	  response(*begin, *begin2);
  }

  template<class ITEM, class POS_EXTRACTOR, class RADIUS_EXTRACTOR>
  struct PosAndRadiusProxy
  {
    using TYPE = PosAndRadiusProxy<ITEM, POS_EXTRACTOR, RADIUS_EXTRACTOR>;
    ITEM &item;
    POS_EXTRACTOR posExtractor;
    RADIUS_EXTRACTOR radiusExtractor;

    constexpr float getRadius() const
    {
      return radiusExtractor(item);
    }

    constexpr Vect<2u, float> getPos() const
    {
      return posExtractor(item);
    }

    struct Builder
    {
      POS_EXTRACTOR posExtractor;
      RADIUS_EXTRACTOR radiusExtractor;

      constexpr TYPE operator()(ITEM &item)
      {
	return TYPE{item, posExtractor, radiusExtractor};
      }
    };
  };

  template<class IT, class POS_EXTRACTOR, class RADIUS_EXTRACTOR>
  constexpr auto makeCircleIteratorAdaptor(IT &&it,
					   POS_EXTRACTOR &&posExtractor,
					   RADIUS_EXTRACTOR &&radiusExtractor)
  {
    return makeProxyIterator(it, PosAndRadiusProxy<decltype(*IT{}), POS_EXTRACTOR, RADIUS_EXTRACTOR>::Builder(posExtractor, radiusExtractor));
  }
};

#endif
