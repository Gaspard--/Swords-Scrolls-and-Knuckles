#include <OgreSceneNode.h>
#include "ParticleEffect.hpp"
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
  Entity entity;

  if (projectileType == ProjectileType::COOLDOWN_RESET)
    {
      entity = Entity(renderer, "feather.mesh");
      entity.getNode()->setScale(1.0f / 4.0f, 1.0f / 4.0f, 1.0f / 4.0f);
    }
  else if (projectileType >= ProjectileType::HEAL && projectileType <= ProjectileType::GOLD50)
    {
      if (projectileType == ProjectileType::HEAL)
	entity = Entity(renderer, "heart.mesh");
      else
	{
	  entity = Entity(renderer, Vect<4u, std::string>{
	      "rupee_green.mesh",
		"rupee_blue.mesh",
		"rupee_red.mesh",
		"rupee_purple.mesh",
		}[projectileType - ProjectileType::GOLD]);
	}
      entity.getNode()->setScale(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
    }
  else if (projectileType != ProjectileType::EXPLOSION &&
	   projectileType != ProjectileType::HIT1 &&
	   projectileType != ProjectileType::HIT2)
    entity = Entity(renderer, "ogrehead.mesh");
  if (entity.getOgre())
    entity.getOgre()->setCastShadows(false);
  return entity;
}

AnimatedEntity EntityFactory::spawnHero(Skins::Skin skin)
{
  AnimatedEntity hero(renderer, skin);

  hero.getEntity().getOgre()->setCastShadows(false);
  hero.getEntity().getNode()->setScale(1.0f / 150.0f, 1.0f / 150.0f, 1.0f / 150.0f);
  (*(hero.getEntity().soundMap))[Sounds::BOYAUX1].setSound(Sounds::BOYAUX1);
  (*(hero.getEntity().soundMap))[Sounds::BOYAUX1].setLooping(true);

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
    light->setDiffuseColour(2.0f, 1.5f, 1.0f);
    light->setSpecularColour(1.0f, 0.5f, 0.5f);
    light->setAttenuation(25, 0.3f, 0.05f, 0.0f);
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

ParticleEffect EntityFactory::createParticleSystem(std::string temp)
{
  static unsigned int count = 0;
  ParticleEffect particleEffect(renderer, temp, std::string("system") + std::to_string(++count));

  particleEffect.getOgre()->setCastShadows(false);
  return particleEffect;
}
