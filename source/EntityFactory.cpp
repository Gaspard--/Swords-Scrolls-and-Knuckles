#include <OgreSceneNode.h>
#include "EntityFactory.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"

Entity EntityFactory::spawnOgreHead()
{
  Entity ogre(renderer, "ogrehead.mesh");

  ogre.getOgre()->setCastShadows(true);
  ogre.getNode()->setScale(1.0f / 150.0f, 1.0f / 150.0f, 1.0f / 150.0f);
  return ogre;
}

AnimatedEntity EntityFactory::spawnSylvanas()
{
  AnimatedEntity sylvanas(renderer, "sylvanas.mesh");

  // TODO : Put the rotation here
  sylvanas.getEntity().getOgre()->setCastShadows(true);
  sylvanas.getEntity().getNode()->setScale(1.0f / 150.0f, 1.0f / 150.0f, 1.0f / 150.0f);
  return sylvanas;
}
