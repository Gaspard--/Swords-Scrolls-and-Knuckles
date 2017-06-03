#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <string>
# include <OgreSceneNode.h>
# include <OgreEntity.h>

# include "Vect.hpp"
# include "Game.hpp"

class Entity
{
protected:
  Ogre::Entity *ogreEntity;
  Ogre::SceneNode *sceneNode;

public:
  constexpr Entity(void)
  : ogreEntity(nullptr)
    , sceneNode(nullptr)
  {}

  Entity(Renderer &renderer,
	 std::string const &mesh);

  Entity(Renderer &renderer,
	 std::string const &mesh,
	 Ogre::SceneNode *parent);

  constexpr Entity(Entity const &e)
  : ogreEntity(e.ogreEntity)
    , sceneNode(e.sceneNode)
  {}

  constexpr Entity(Entity &&e)
  : ogreEntity(std::move(e.ogreEntity))
    , sceneNode(std::move(e.sceneNode))
  {}

  Entity &operator=(Entity const &e) = default;
  Entity &operator=(Entity &&e) = default;
  ~Entity(void) = default;

  /// Get the ogre's version of this entity.
  Ogre::Entity *getOgre(void);
  Ogre::Entity const *getOgre(void) const;

  /// Get the node attached to this entity.
  Ogre::SceneNode *getNode(void);
  Ogre::SceneNode const *getNode(void) const;

  /// Shortcut to Entity::getNode().setPosition()
  void setPosition(float x, float y, float z);
  void setPosition(Vect<3, float> pos);
  void setPosition(Ogre::Vector3 pos);
};

#endif // !ENTITY_HPP
