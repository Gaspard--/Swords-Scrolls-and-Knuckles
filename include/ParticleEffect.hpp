#ifndef PARTICLE_EFFECT_HPP
# define PARTICLE_EFFECT_HPP

# include <OgreParticleSystem.h>
# include <string>
# include <OgreSceneNode.h>
# include "Vect.hpp"

class Renderer;

class ParticleEffect
{
  Ogre::ParticleSystem *ogreParticleEffect;
  Ogre::SceneNode *sceneNode;

public:
  constexpr ParticleEffect(void)
    : ogreParticleEffect(nullptr)
    , sceneNode(nullptr)
  {}

  ParticleEffect(Renderer &renderer,
		 std::string const &temp,
		 std::string const &name);

  ParticleEffect(std::string const &temp,
		 std::string const &name,
		 Ogre::SceneNode *parent);

  // TODO Constexpr
  ParticleEffect(ParticleEffect &&e)
    : ogreParticleEffect(nullptr)
    , sceneNode(nullptr)
  {
    std::swap(ogreParticleEffect, e.ogreParticleEffect);
    std::swap(sceneNode, e.sceneNode);
  }

  ParticleEffect &operator=(ParticleEffect const &e) = delete;
  ParticleEffect &operator=(ParticleEffect &&e);

  ~ParticleEffect(void);

  /// Get the ogre's version of this entity.
  Ogre::ParticleSystem *getOgre(void);
  Ogre::ParticleSystem const *getOgre(void) const;

  /// Get the node attached to this entity.
  Ogre::SceneNode *getNode(void);
  Ogre::SceneNode const *getNode(void) const;
  void reasignNode(Ogre::SceneNode *);

  void setPosition(float x, float y, float z);
  void setPosition(Vect<3, float> pos);
  void setPosition(Ogre::Vector3 pos);

  void setDirection(Vect<2u, Ogre::Real> v);

};

#endif
