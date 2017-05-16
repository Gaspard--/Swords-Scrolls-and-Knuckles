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
  ogre = Entity("ogrehead.mesh");
  ogre.setPosition(0, 50, 0);
  ogre.getOgre()->setCastShadows(true);

  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton()
    .createPlane("ground",
		 Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		 plane,
		 1500, 1500, 20, 20,
		 true,
		 1, 5, 5,
		 Ogre::Vector3::UNIT_Z);

  ground = Entity("ground");
  ground.getOgre()->setCastShadows(false);
  ground.getOgre()->setMaterialName("rockwall");

  // Lights
  _renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));
  Ogre::Light *light = _renderer.getSceneManager().createLight("MainLight");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDiffuseColour(1.0, 1.0, 1.0);
  light->setSpecularColour(1.0, 1.0, 1.0);
  light->setDirection(-1, -1, -1);
  light->setPosition(50, 100, 50);
  light->setAttenuation(500, 1.0f, 0.007f, 0.0f);

  // Keys callback
  Keyboard::getKeyboard().registerCallback(OIS::KC_W, [this](bool) {
					   cameraNode->translate(10, 0, 0);
					   return (true);
					   });

  std::clog << "End loading" << std::endl;
}
