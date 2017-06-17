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
  mount->getEntity().getOgre()->setCastShadows(false);
  archer.setMount(mount);

  // Light 1
  {
    auto light(renderer.getSceneManager().createLight());
    auto sceneNode(archer.getEntity().getNode()->createChildSceneNode());

    light->setType(Ogre::Light::LT_POINT);
    light->setDiffuseColour(1.f, 1.f, 1.f);
    light->setSpecularColour(1.0f, 1.0f, 1.0f);
    light->setAttenuation(100, 0.5f, 0.001f, 0.0f);
    sceneNode->attachObject(light);
    sceneNode->setPosition(75, 75, 75);
  }
 
  return (archer);
}

AnimatedEntity EntityFactory::spawnEnemy()
{
  AnimatedEntity enemy(renderer, "ennemy1.mesh");

  enemy.getEntity().getOgre()->setCastShadows(true);
  enemy.getEntity().getNode()->setScale(1.0f / 300.0f, 1.0f / 300.0f, 1.0f / 300.0f);
  return enemy;
}
