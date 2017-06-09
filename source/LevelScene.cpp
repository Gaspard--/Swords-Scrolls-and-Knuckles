#include <OgreEntity.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include <OgreManualObject.h>
#include "LevelScene.hpp"
#include "Entity.hpp"

LevelScene::LevelScene(Renderer &renderer)
  : terrainNode(renderer.getSceneManager().getRootSceneNode()->createChildSceneNode())
  , cameraNode([&renderer]()
	       {
		 auto cameraNode(renderer.getSceneManager().getRootSceneNode()->createChildSceneNode());

		 cameraNode->attachObject(&renderer.getCamera());
		 cameraNode->setPosition(Ogre::Vector3(8, 13, 5 + 8));
		 cameraNode->lookAt(Ogre::Vector3(8, 0, 8), Ogre::Node::TS_WORLD);
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
			    25000, 25000, 1, 1,
			    true,
			    1, 25000, 25000,
			    Ogre::Vector3::UNIT_Z);
	     Entity ground(renderer, "ground");

	     ground.getOgre()->setCastShadows(false);
	     ground.getOgre()->setMaterialName("wall");
	     return ground;
	   }())
  , logicThread(*this, renderer, players)
{
  renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

  {
    AnimatedEntity illidan(renderer, "illidan.mesh");

    illidan.getEntity().getOgre()->setCastShadows(true);
    illidan.getEntity().getNode()->setScale(1.0 / 150.0, 1.0 / 150.0, 1.0 / 150.0);
    players.push_back(std::move(illidan));
  }
  {
    AnimatedEntity illidan(renderer, "illidan.mesh");

    illidan.getEntity().getOgre()->setCastShadows(true);
    illidan.getEntity().getNode()->setScale(1.0 / 150.0, 1.0 / 150.0, 1.0 / 150.0);
    players.push_back(std::move(illidan));
  }

  // obviously horrible & will be replaced.
  auto light(renderer.getSceneManager().createLight("MainLight"));

  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDiffuseColour(1.0, 0.7, 0.4);
  light->setSpecularColour(1.0, 0.5, 1.0);
  light->setDirection(0.7, -0.8, -0.5);
  light->setPosition(50, 100, 50);
  light->setAttenuation(500, 1.0f, 0.007f, 0.0f);

  terrainNode->scale(1.0, 1.0, 1.0);
}

void LevelScene::setTerrain(Terrain const &terrain)
{
  for (unsigned int i(0); i < 100; ++i)
    {
      for (unsigned int j(0); j < 100; ++j)
	{
	  if (terrain.getTile({i, j}).isSolid)
	    {
	      Ogre::SceneNode *wallNode(terrainNode->createChildSceneNode());
	      Ogre::Entity* wall(wallNode->getCreator()->createEntity("WallMesh"));

	      wall->setCastShadows(true);
	      wallNode->attachObject(wall);
	      wallNode->setPosition(i, 0, j);
	    }
	}
    }
}

void LevelScene::createWallMesh()
{
  constexpr double const dim(1.0);
  Ogre::ManualObject obj("WallObject");

  obj.begin("wall", Ogre::RenderOperation::OT_TRIANGLE_LIST); // TODO: add multiple material(s) ?

  unsigned int offset(0u);
  { // make the 3 walls
    Vect<3u, double> start{0.0, 0.0, 0.0};
    Vect<3u, double> up{0.0, 1.0, 0.0};
    Vect<3u, double> right{0.0, 0.0, 1.0};

    for (unsigned int i(0); i < 3; ++i)
      {
	for (Vect<2u, double> const &coef : {Vect<2u, double>(0, 0), Vect<2u, double>(1, 0),
	      Vect<2u, double>(0, 1), Vect<2u, double>(1, 1)})
	  {
	    Vect<3u, double> const pos((start + right * coef[0] + up * coef[1]) * dim);

	    obj.position(pos[0], pos[1], pos[2]);
	    obj.textureCoord(coef[0], coef[1]);
	  }
	start = start + right;
	right = {right[2], 0, -right[0]};

	obj.triangle(offset, offset + 1, offset + 3);
	obj.triangle(offset, offset + 3, offset + 2);
	offset += 4;
      }
  }
  { // make the roof
    Vect<3u, double> start{0.0, 1.0, 0.0};
    Vect<3u, double> up{0.0, 0.0, 1.0};
    Vect<3u, double> right{1.0, 0.0, 0.0};

    for (Vect<2u, double> const &coef : {
  	Vect<2u, double>(0, 0), Vect<2u, double>(1, 0),
  	  Vect<2u, double>(0, 1), Vect<2u, double>(1, 1)})
      {
  	Vect<3u, double> const pos((start + right * coef[0] + up * coef[1]) * dim);

  	obj.position(pos[0], pos[1], pos[2]);
  	obj.textureCoord(coef[0], coef[1]);
      }

    obj.triangle(offset, offset + 3, offset + 1);
    obj.triangle(offset, offset + 2, offset + 3);
    offset += 4;
  }
  obj.end();
  obj.convertToMesh("WallMesh");
}

bool LevelScene::update(Game &, Ogre::FrameEvent const &)
{
  std::cout << "\ncamera : " << cameraNode->getPosition() << std::endl;
  logicThread->updateDisplay(*this);
  return true;
}
