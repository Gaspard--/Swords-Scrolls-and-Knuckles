#include <OgreSceneNode.h>
#include "EntityFactory.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"
#include "Projectile.hpp"

Entity EntityFactory::spawnOgreHead(void)
{
  Entity ogre(renderer, "ogrehead.mesh");

  ogre.getOgre()->setCastShadows(false);
  ogre.getNode()->setScale(1.0f / 150.0f, 1.0f / 150.0f, 1.0f / 150.0f);
  return ogre;
}

Entity EntityFactory::spawnProjectile(unsigned int projectileType)
{
  Entity entity(renderer, "ogrehead.mesh");

  if (projectileType == ProjectileType::COOLDOWN_RESET)
    entity = Entity(renderer, "feather.mesh");
  else if (projectileType == ProjectileType::HEAL)
    entity = Entity(renderer, "heart.mesh");
  else
    entity = Entity(renderer, "rupee.mesh");
  entity.getOgre()->setCastShadows(false);
  entity.getNode()->setScale(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
  return entity;
}

AnimatedEntity EntityFactory::spawnHero(Skins::Skin skin)
{
  AnimatedEntity hero(renderer, skin);

  hero.getEntity().getOgre()->setCastShadows(false);
  hero.getEntity().getNode()->setScale(1.0f / 150.0f, 1.0f / 150.0f, 1.0f / 150.0f);
  (*(hero.getEntity().soundMap))[Sounds::FOOTSTEPS].setSound(Sounds::FOOTSTEPS);
  (*(hero.getEntity().soundMap))[Sounds::FOOTSTEPS].setLooping(true);
  (*(hero.getEntity().soundMap))[Sounds::FOOTSTEPS].setVolume(10000.f);

  // Mount
  AnimatedEntity *mount(new AnimatedEntity("wolf.mesh", hero.getEntity().getNode()));
  mount->getEntity().getOgre()->setCastShadows(false);
  mount->getEntity().getNode()->setPosition(0, -150.f, 0);
  hero.setMount(mount);

  // Light 1
  {
    auto light(renderer.getSceneManager().createLight());
    auto sceneNode(hero.getEntity().getNode()->createChildSceneNode());

    light->setType(Ogre::Light::LT_POINT);
    light->setDiffuseColour(1.f, 1.f, 1.f);
    light->setSpecularColour(1.0f, 1.0f, 1.0f);
    light->setAttenuation(100, 0.5f, 0.001f, 0.0f);
    sceneNode->attachObject(light);
    sceneNode->setPosition(0, 150, 0);
  }
  return (hero);
}

AnimatedEntity EntityFactory::spawnEnemy()
{
  AnimatedEntity enemy(renderer, "ennemy1.mesh");

  enemy.getEntity().getOgre()->setCastShadows(false);
  enemy.getEntity().getNode()->setScale(1.0f / 300.0f, 1.0f / 300.0f, 1.0f / 300.0f);
  return enemy;
}
