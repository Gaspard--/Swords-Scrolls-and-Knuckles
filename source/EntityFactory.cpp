#include "EntityFactory.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"

Entity EntityFactory::spawnOgreHead()
{
  Entity ogre(renderer, "ogrehead.mesh");

  ogre.getOgre()->setCastShadows(true);
  ogre.getNode()->setScale(1.0 / 150.0, 1.0 / 150.0, 1.0 / 150.0);
  return ogre;
}

AnimatedEntity EntityFactory::spawnIllidan()
{
  AnimatedEntity illidan(renderer, "illidan.mesh");

  illidan.getEntity().getOgre()->setCastShadows(true);
  return illidan;
}
