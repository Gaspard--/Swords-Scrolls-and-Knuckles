#include <OgreVector3.h>
#include "Entity.hpp"

Entity::Entity(Renderer &renderer,
	       std::string const &mesh)
  : Entity(mesh, renderer.getSceneManager().getRootSceneNode())
{
}

Entity::Entity(std::string const &mesh, Ogre::SceneNode *parent)
  : ogreEntity(parent->getCreator()->createEntity(mesh))
  , sceneNode(parent->createChildSceneNode())
{
  sceneNode->attachObject(ogreEntity);
}

Entity &Entity::operator=(Entity &&e)
{
  std::swap(ogreEntity, e.ogreEntity);
  std::swap(sceneNode, e.sceneNode);

  return *this;
}

Entity::~Entity()
{
  if (sceneNode)
    {
      sceneNode->getCreator()->destroyEntity(ogreEntity);
      sceneNode->getCreator()->destroySceneNode(sceneNode);
    }
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
  sceneNode->setPosition(v[0], v[1], v[2]);
}

void Entity::setDirection(Vect<2u, Ogre::Real> v)
{
  if (v.length2() > 0)
    {
      v = v.unsafeNormalized();
      sceneNode->setDirection(v[0], 0, v[1], Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
    }
}

void Entity::setPosition(Ogre::Vector3 pos)
{
  sceneNode->setPosition(pos);
}
