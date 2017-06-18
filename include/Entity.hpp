#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <string>
# include <OgreSceneNode.h>
# include <OgreEntity.h>
# include <unordered_map>

# include "AudioSource.hpp"
# include "Vect.hpp"
# include "Game.hpp"

class Entity
{
protected:
  Ogre::Entity *ogreEntity;
  Ogre::SceneNode *sceneNode;

  void updateSoundsPos(void);

public:
  std::unique_ptr<std::unordered_map<Sounds, AudioSource>> soundMap;

  constexpr Entity(void)
    : ogreEntity(nullptr)
    , sceneNode(nullptr)
    , soundMap(nullptr)
  {}

  Entity(Renderer &renderer,
    std::string const &mesh);

  Entity(std::string const &mesh,
    Ogre::SceneNode *parent);

  Entity(Entity const &) = delete;

  // TODO Constexpr
  Entity(Entity &&e)
    : ogreEntity(nullptr)
    , sceneNode(nullptr)
  {
    std::swap(ogreEntity, e.ogreEntity);
    std::swap(sceneNode, e.sceneNode);
    std::swap(soundMap, e.soundMap);
  }

  Entity &operator=(Entity const &e) = delete;
  Entity &operator=(Entity &&e);

  ~Entity(void);

  /// Get the ogre's version of this entity.
  Ogre::Entity *getOgre(void);
  Ogre::Entity const *getOgre(void) const;

  /// Get the node attached to this entity.
  Ogre::SceneNode *getNode(void);
  Ogre::SceneNode const *getNode(void) const;
  void reasignNode(Ogre::SceneNode *);

  /// Shortcut to Entity::getNode().setPosition()
  void setPosition(float x, float y, float z);
  void setPosition(Vect<3, float> pos);
  void setPosition(Ogre::Vector3 pos);

  void setDirection(Vect<2u, Ogre::Real> v);
};

#endif // !ENTITY_HPP
