#include <iostream>
#include <OgreVector3.h>
#include "ParticleEffect.hpp"
#include "Renderer.hpp"

ParticleEffect::ParticleEffect(Renderer &renderer,
			       std::string const &temp,
			       std::string const &name)
  : ParticleEffect(temp, name, renderer.getSceneManager().getRootSceneNode())
{
}

ParticleEffect::ParticleEffect(std::string const &temp, std::string const &name, Ogre::SceneNode *parent)
  : ogreParticleEffect(parent->getCreator()->createParticleSystem(name, temp))
  , sceneNode(parent->createChildSceneNode())
{
  sceneNode->attachObject(ogreParticleEffect);
}

ParticleEffect &ParticleEffect::operator=(ParticleEffect &&e)
{
  if (sceneNode)
    {
      std::cout << "[Particles] destroying particle effect!" << std::endl;
      sceneNode->getCreator()->destroyParticleSystem(ogreParticleEffect);
      sceneNode->getCreator()->destroySceneNode(sceneNode);
    }
  ogreParticleEffect = e.ogreParticleEffect;
  sceneNode = e.sceneNode;
  e.ogreParticleEffect = nullptr;
  e.sceneNode = nullptr;
  return *this;
}

ParticleEffect::~ParticleEffect()
{
  if (sceneNode)
    {
      std::cout << "[Particles] destroying particle effect!" << std::endl;
      sceneNode->getCreator()->destroyParticleSystem(ogreParticleEffect);
      sceneNode->getCreator()->destroySceneNode(sceneNode);
    }
}

Ogre::ParticleSystem *ParticleEffect::getOgre(void)
{
  return (ogreParticleEffect);
}

Ogre::ParticleSystem const *ParticleEffect::getOgre(void) const
{
  return (ogreParticleEffect);
}

Ogre::SceneNode *ParticleEffect::getNode(void)
{
  return (sceneNode);
}

Ogre::SceneNode const *ParticleEffect::getNode(void) const
{
  return (sceneNode);
}

void ParticleEffect::reasignNode(Ogre::SceneNode *node) {
  sceneNode->detachObject(ogreParticleEffect);
  node->attachObject(ogreParticleEffect);
  sceneNode = node;
}

void ParticleEffect::setPosition(float x, float y, float z)
{
  sceneNode->setPosition(x, y, z);
}

void ParticleEffect::setPosition(Vect<3, float> v)
{
  sceneNode->setPosition(v[0], v[1], v[2]);
}

void ParticleEffect::setDirection(Vect<2u, Ogre::Real> v)
{
  if (v.length2() > 0)
    {
      v = v.unsafeNormalized();
      sceneNode->setDirection(v[0], 0, v[1], Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
    }
}

void ParticleEffect::setPosition(Ogre::Vector3 pos)
{
  sceneNode->setPosition(pos);
}
