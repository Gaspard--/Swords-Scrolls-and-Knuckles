#include "Entity.hpp"

Entity::Entity(Renderer &renderer,
	       std::string const &mesh)
  : ogreEntity(renderer.getSceneManager().createEntity(mesh))
  , sceneNode(renderer.getSceneManager().getRootSceneNode()->createChildSceneNode())
{
  sceneNode->attachObject(ogreEntity);
}

Entity::Entity(Renderer &renderer,
	       std::string const &mesh,
	       Ogre::SceneNode *parent)
  : ogreEntity(renderer.getSceneManager().createEntity(mesh))
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

Ogre::SceneNode *Entity::getNode(void)
{
  return (sceneNode);
}

Ogre::SceneNode const *Entity::getNode(void) const
{
  return (sceneNode);
}

void Entity::setPosition(float x, float y, float z)
{
  sceneNode->setPosition(x, y, z);
}

void Entity::setPosition(Vect<3, float> v)
{
  sceneNode->setPosition(v.x(), v.y(), v.z());
}

void Entity::setPosition(Ogre::Vector3 pos)
{
  sceneNode->setPosition(pos);
}
