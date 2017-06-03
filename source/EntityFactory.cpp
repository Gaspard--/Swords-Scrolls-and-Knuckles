#include "EntityFactory.hpp"
#include "Entity.hpp"

Entity EntityFactory::spawnOgreHead()
{
  Entity ogre(renderer, "ogrehead.mesh");

  ogre.getOgre()->setCastShadows(false);
  ogre.getOgre()->setMaterialName("Ogre.mtl");
  return ogre;
}
