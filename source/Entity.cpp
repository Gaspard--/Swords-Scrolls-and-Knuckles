#include "Entity.hpp"

Entity::Entity(std::string const &mesh, Ogre::SceneNode *parent)
  : ogreEntity(Game::getGame().getRenderer().getSceneManager().createEntity(mesh))
  , sceneNode(parent->createChildSceneNode())

{
  sceneNode->attachObject(ogreEntity);
}

Ogre::Entity *Entity::getOgre(void)
{
  return (ogreEntity);
}

Ogre::Entity const *Entity::getOgre(void) const
{
  return (ogreEntity);
}

void Entity::setPosition(float x, float y, float z)
{
  sceneNode->setPosition(x, y, z);
}

void Entity::setPosition(Vect<3, float> v)
{
  sceneNode->setPosition(v[0], v[1], v[2]);
}

void Entity::setPosition(Ogre::Vector3 pos)
{
  sceneNode->setPosition(pos);
}
