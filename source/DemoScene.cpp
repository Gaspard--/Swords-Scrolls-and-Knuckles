#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include "DemoScene.hpp"
#include "Game.hpp"

DemoScene::DemoScene(void)
  : Scene()
{}

void DemoScene::load(void)
{
  std::clog << "Loading demo scene" << std::endl;

  // Camera
  cameraNode = _renderer.getSceneManager().getRootSceneNode()->createChildSceneNode();
  cameraNode->attachObject(&_renderer.getCamera());
  cameraNode->setPosition(Ogre::Vector3(0, 300, 500));
  cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  _renderer.getCamera().setNearClipDistance(5);

  // Entities
  Ogre::Entity *ogreEntity = _renderer.getSceneManager().createEntity("ogrehead.mesh");
  Ogre::SceneNode *ogreNode = _renderer.getSceneManager().getRootSceneNode()->createChildSceneNode();
  ogreNode->setPosition(0, 50, 0);
  ogreNode->attachObject(ogreEntity);
  ogreEntity->setCastShadows(true);

  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton()
    .createPlane("ground",
		 Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		 plane,
		 1500, 1500, 20, 20,
		 true,
		 1, 5, 5,
		 Ogre::Vector3::UNIT_Z);
  Ogre::Entity *groundEntity = _renderer.getSceneManager().createEntity("ground");
  groundEntity->setCastShadows(false);
  groundEntity->setMaterialName("rockwall");
  _renderer.getSceneManager().getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

  // Lights
  _renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));
  _renderer.getSceneManager().setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  Ogre::Light *light = _renderer.getSceneManager().createLight("MainLight");
  light->setType(Ogre::Light::LT_SPOTLIGHT);
  light->setDiffuseColour(1.0, 1.0, 1.0);
  light->setSpecularColour(1.0, 1.0, 1.0);
  light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
  light->setDirection(-1, -1, -1);
  light->setPosition(100, 100, 100);

  std::clog << "End loading" << std::endl;
}
