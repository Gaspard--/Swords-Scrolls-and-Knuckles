#include <OgreSceneNode.h>
#include "EntityFactory.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"

Entity EntityFactory::spawnOgreHead(void)
{
  Entity ogre(renderer, "ogrehead.mesh");

  ogre.getOgre()->setCastShadows(true);
  ogre.getNode()->setScale(1.0f / 150.0f, 1.0f / 150.0f, 1.0f / 150.0f);
  return ogre;
}

AnimatedEntity EntityFactory::spawnArcher(Skins::Skin skin)
{
  AnimatedEntity archer(renderer, skin);

  archer.getEntity().getOgre()->setCastShadows(true);
  archer.getEntity().getNode()->setScale(1.0f / 150.0f, 1.0f / 150.0f, 1.0f / 150.0f);
  (*(archer.getEntity().soundMap))[Sounds::BOYAUX1].setSound(Sounds::BOYAUX1);
  (*(archer.getEntity().soundMap))[Sounds::BOYAUX1].setLooping(true);


  // Mount
  AnimatedEntity *mount(new AnimatedEntity("wolf.mesh", archer.getEntity().getNode()));
  mount->getEntity().getOgre()->setCastShadows(true);
  mount->getEntity().getNode()->translate(0.f, -150.f, 0.f); // Put the mount under the player
  archer.setMount(mount);
  return (archer);
}

AnimatedEntity EntityFactory::spawnEnemy()
{
  AnimatedEntity enemy(renderer, "ennemy1.mesh");

  // TODO : Put the rotation here
  enemy.getEntity().getOgre()->setCastShadows(true);
  enemy.getEntity().getNode()->setScale(1.0f / 300.0f, 1.0f / 300.0f, 1.0f / 300.0f);
  return enemy;
}
