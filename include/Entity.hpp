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
    Entity(void) = default;
    Entity(std::string const &mesh,
	   Ogre::SceneNode *parent = Game::getGame().getRenderer().getSceneManager().getRootSceneNode());
    Entity(Entity const &) = default;
    Entity(Entity &&) = default;
    Entity &operator=(Entity const &) = default;
    Entity &operator=(Entity &&) = default;
    virtual ~Entity(void) = default;

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
