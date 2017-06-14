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
  , soundMap(new std::unordered_map<Sounds, AudioSource>)
{
  sceneNode->attachObject(ogreEntity);
}

Entity &Entity::operator=(Entity &&e)
{
  std::swap(ogreEntity, e.ogreEntity);
  std::swap(sceneNode, e.sceneNode);
  std::swap(soundMap, e.soundMap);

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
  updateSoundsPos();
}

void Entity::setPosition(Vect<3, float> v)
{
  sceneNode->setPosition(v[0], v[1], v[2]);
  updateSoundsPos();
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
  updateSoundsPos();
}

void Entity::updateSoundsPos(void)
{
  for (auto &sound : *soundMap)
    {
      sound.second.setPos(sceneNode->getPosition());
    }
}
