#include <OgreEntity.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include "LevelScene.hpp"
#include "Entity.hpp"

LevelScene::LevelScene(Renderer &renderer)
  : cameraNode([&renderer]()
	       {
		 auto cameraNode(renderer.getSceneManager().getRootSceneNode()->createChildSceneNode());
      
		 cameraNode->attachObject(&renderer.getCamera());
		 cameraNode->setPosition(Ogre::Vector3(0, 300, 500));
		 cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
		 renderer.getCamera().setNearClipDistance(5);
		 return cameraNode;
	       }())
  , ground([&renderer]()
	   {
	     Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	     Ogre::MeshManager::getSingleton()
	       .createPlane("ground",
			    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			    plane,
			    1500, 1500, 20, 20,
			    true,
			    1, 5, 5,
			    Ogre::Vector3::UNIT_Z);

	     auto ground(Entity(renderer, "ground"));

	     ground.getOgre()->setCastShadows(false);
	     ground.getOgre()->setMaterialName("rockwall");
	     return ground;
	   }())
  , logicThread(*this, renderer)
{
  renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

  // obviously horrible & will be replaced.
  auto light(renderer.getSceneManager().createLight("MainLight"));
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDiffuseColour(1.0, 1.0, 0.0);
  light->setSpecularColour(1.0, 0.0, 1.0);
  light->setDirection(-1, -1, -1);
  light->setPosition(50, 100, 50);
  light->setAttenuation(500, 1.0f, 0.007f, 0.0f);
}

LevelScene::~LevelScene()
{
}

bool LevelScene::update(Game &, Ogre::FrameEvent const &)
{
  logicThread->updateDisplay(*this);
  return true;
}

