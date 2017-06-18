#include <OgreEntity.h>
#include <OgreLight.h>
#include <OgreSceneNode.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include <OgreManualObject.h>
#include "EntityFactory.hpp"
#include "LevelScene.hpp"
#include "Entity.hpp"
#include "AudioSource.hpp"

LevelScene::LevelScene(Renderer &renderer, std::vector<std::function<AnimatedEntity(Renderer &)>> const &v, std::vector<enum class PlayerId> const &classes)
  : uiHUD(renderer)
  , uiPause(*this, renderer)
  , terrainNode(renderer.getSceneManager().getRootSceneNode()->createChildSceneNode())
  , inPause(false)
  , cameraNode([&renderer]()
	       {
		 auto cameraNode(renderer.getSceneManager().getRootSceneNode()->createChildSceneNode());

		 cameraNode->attachObject(&renderer.getCamera());
		 cameraNode->setPosition(Ogre::Vector3(8, 13, 5 + 8));
		 cameraNode->lookAt(Ogre::Vector3(8, 0, 8), Ogre::Node::TS_WORLD);
		 renderer.getCamera().setNearClipDistance(5);
		 return cameraNode;
	       }())
  , logicThread(*this, renderer, players, classes)
    // , music(Musics::SMALL_WORLD)
{
  // music.setVolume(0.2f);
  // music.play();

  renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f));

  std::clog << "Loading level scene" << std::endl;

  std::clog << "SIZE BITCH : " << v.size() << std::endl;
  for (auto const &fn : v) {
    players.push_back(std::move(fn(renderer)));
  }

  terrainNode->scale(1.0, 1.0, 1.0);

  // Hide pause
  uiPause.setUIVisible(false);

  std::clog << "End loading level scene" << std::endl;
}

LevelScene::~LevelScene() {
  if (isInPause()) {
    logicThread->unpause();
    inPause = false;
    uiPause.setUIVisible(false);
  }
}

void LevelScene::resetSceneCallbacks(Renderer &r) {
  InputCallbacks::clearAllCallbacks();
  if (uiPause.isVisible())
    uiPause.resetUICallbacks();
  else
    {
      // For demonstration / test purpose. Remove it if needed.
      auto const setMounted([this](bool b, size_t = 0) {
	  if (!b && !isInPause())
	    for (auto &p : players) {
	      p.setMounted(!p.isMounted());
	    }
	});
      Keyboard::getKeyboard().registerCallback(OIS::KC_SPACE, setMounted);
      Joystick::registerGlobalCallback(joystickState::JS_A, setMounted);

      // Go back to menu
      auto const goBackToMenu([this, &r](bool b, size_t = 0) {
	  if (!b)
	    {
	      if (uiPause.getOverlay()->isVisible()) {
		unpauseScene(r);
	      } else {
		pauseScene(r);
	      }
	    }
	});
      Keyboard::getKeyboard().registerCallback(OIS::KC_ESCAPE, goBackToMenu);
      Joystick::registerGlobalCallback(joystickState::JS_START, goBackToMenu);
    }
}
void LevelScene::setTerrain(Terrain const &terrain)
{
  for (unsigned int i(0); i < terrain.getSize()[0]; ++i)
    {
      for (unsigned int j(0); j < terrain.getSize()[1]; ++j)
	{
	      
	  if (terrain.getTile({i, j}).isSolid)
	    {
	      Ogre::SceneNode *wallNode(terrainNode->createChildSceneNode());
	      Ogre::Entity* wall(wallNode->getCreator()->createEntity("WallMesh"));

	      wall->setCastShadows(true);
	      wallNode->attachObject(wall);
	      wallNode->setPosition(static_cast<Ogre::Real>(i), 0.0f, static_cast<Ogre::Real>(j));
	    }
	  else
	    {
	      Ogre::SceneNode *wallNode(terrainNode->createChildSceneNode());
	      Ogre::Entity* ground(wallNode->getCreator()->createEntity("GroundMesh"));

	      ground->setCastShadows(true);
	      wallNode->attachObject(ground);
	      wallNode->setPosition(static_cast<Ogre::Real>(i), 0.0f, static_cast<Ogre::Real>(j));
	    }
	}
    }
}

void LevelScene::createGroundMesh()
{
  constexpr double const dim(1.0);
  Ogre::ManualObject obj("GroundObject");
  unsigned int offset(0u);

  obj.begin("wall", Ogre::RenderOperation::OT_TRIANGLE_LIST); // TODO: add multiple material(s) ?
  {
    Vect<3u, double> up{ 0.0, 0.0, 1.0 };
    Vect<3u, double> right{ 1.0, 0.0, 0.0 };

    for (Vect<2u, double> const &coef : {
  	Vect<2u, double>(0.0, 0.0), Vect<2u, double>(1.0, 0.0),
  	  Vect<2u, double>(0.0, 1.0), Vect<2u, double>(1.0, 1.0)})
      {
  	Vect<3u, double> const pos((right * coef[0] + up * coef[1]) * dim);

	obj.position(
		     static_cast<Ogre::Real>(pos[0]),
		     static_cast<Ogre::Real>(pos[1]),
		     static_cast<Ogre::Real>(pos[2])
		     );
	obj.normal(0.0f, 1.0f, 0.0f);
	obj.textureCoord(
			 static_cast<Ogre::Real>(coef[0]),
			 static_cast<Ogre::Real>(coef[1])
			 );
      }

    obj.triangle(offset, offset + 3, offset + 1);
    obj.triangle(offset, offset + 2, offset + 3);
    offset += 4;
  }
  obj.end();
  obj.convertToMesh("GroundMesh");
}

void LevelScene::createWallMesh()
{
  constexpr double const dim(1.0);
  Ogre::ManualObject obj("WallObject");

  obj.begin("wall", Ogre::RenderOperation::OT_TRIANGLE_LIST); // TODO: add multiple material(s) ?
  unsigned int offset(0u);
  { // make the 3 walls
    Vect<3u, double> start{ 0.0, 0.0, 0.0 };
    Vect<3u, double> const up{ 0.0, 2.0, 0.0 };
    Vect<3u, double> right{ 0.0, 0.0, 1.0 };

    for (unsigned int i(0); i < 4; ++i)
      {
	for (Vect<2u, double> const &coef : {Vect<2u, double>(0.0, 0.0), Vect<2u, double>(1.0, 0.0),
	      Vect<2u, double>(0.0, 1.0), Vect<2u, double>(1.0, 1.0)})
	  {
	    Vect<3u, double> const pos((start + right * coef[0] + up * coef[1]) * dim);

	    obj.position(static_cast<Ogre::Real>(pos[0]),
			 static_cast<Ogre::Real>(pos[1]),
			 static_cast<Ogre::Real>(pos[2])
			 );
	    obj.normal(static_cast<Ogre::Real>(-right[2]), 0.0f, static_cast<Ogre::Real>(right[0]));
	    obj.textureCoord(static_cast<Ogre::Real>(coef[0]),
			     static_cast<Ogre::Real>(coef[1] * 2)
			     );
	  }
	start = start + right;
	right = {right[2], 0.0, -right[0]};

	obj.triangle(offset, offset + 1, offset + 3);
	obj.triangle(offset, offset + 3, offset + 2);
	offset += 4;
      }
  }
  {
    Vect<3u, double> start{ 0.0, 2.0, 0.0 };
    Vect<3u, double> up{ 0.0, 0.0, 1.0 };
    Vect<3u, double> right{ 1.0, 0.0, 0.0 };

    for (Vect<2u, double> const &coef : {
	Vect<2u, double>(0.0, 0.0), Vect<2u, double>(1.0, 0.0),
	  Vect<2u, double>(0.0, 1.0), Vect<2u, double>(1.0, 1.0)})
      {
	Vect<3u, double> const pos((start + right * coef[0] + up * coef[1]) * dim);

	obj.position(
		     static_cast<Ogre::Real>(pos[0]),
		     static_cast<Ogre::Real>(pos[1]),
		     static_cast<Ogre::Real>(pos[2])
		     );
	obj.normal(0.0, 1.0, 0.0);
	obj.textureCoord(
			 static_cast<Ogre::Real>(coef[0]),
			 static_cast<Ogre::Real>(coef[1])
			 );
      }

    obj.triangle(offset, offset + 3, offset + 1);
    obj.triangle(offset, offset + 2, offset + 3);
    offset += 4;
  }

  obj.end();
  obj.convertToMesh("WallMesh");
  createGroundMesh();
}

bool LevelScene::update(Game &, Ogre::FrameEvent const &)
{
  if (!isInPause()) {
    logicThread->updateDisplay(*this);
  }
  // music.update();
  return true;
}

bool LevelScene::isInPause(void) const {
  return (inPause);
}

void LevelScene::updateUI(std::vector<Player> const &v) {
  uiHUD.updateHUD(v);
}

void LevelScene::pauseScene(Renderer &r) {
  logicThread->pause();
  inPause = true;
  uiPause.setUIVisible(true);
  resetSceneCallbacks(r);
}

void LevelScene::unpauseScene(Renderer &r) {
  logicThread->unpause();
  inPause = false;
  uiPause.setUIVisible(false);
  resetSceneCallbacks(r);
}
