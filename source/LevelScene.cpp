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

LevelScene::LevelScene(Renderer &renderer)
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
// , music(Musics::SMALL_WORLD)
{
  // music.setVolume(0.2f);
  // music.play();
  renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));

  std::clog << "Loading level scene" << std::endl;

  {
    EntityFactory ef(renderer);

    players.push_back(std::move(ef.spawnArcher(Skins::Archer::BASE)));
    players.push_back(std::move(ef.spawnArcher(Skins::Archer::BASE)));
  }

  // obviously horrible & will be replaced.
  auto light(renderer.getSceneManager().createLight("MainLight"));

  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDiffuseColour(1.0f, 0.7f, 0.4f);
  light->setSpecularColour(1.0f, 0.5f, 1.0f);
  light->setDirection(0.7f, -0.8f, -0.5f);
  light->setPosition(50, 100, 50);
  light->setAttenuation(500, 1.0f, 0.007f, 0.0f);

  terrainNode->scale(1.0, 1.0, 1.0);

  // Hide pause
  uiPause.setUIVisible(false);

  std::clog << "End loading level scene" << std::endl;
}

LevelScene::~LevelScene() {
  if (isInPause()) {
    unpauseScene();
  }
}

void LevelScene::resetSceneCallbacks(void) {
  InputCallbacks::clearAllCallbacks();
  if (uiPause.isVisible())
    uiPause.resetUICallbacks();
  else
  {
    // For demonstration / test purpose. Remove it if needed.
    auto const setMounted([this](bool b, size_t i = 0) {
      if (!b && !isInPause())
      {
	for (auto &p : players) {
	  p.setMounted(!p.isMounted());
	}
      }
    });
    Keyboard::getKeyboard().registerCallback(OIS::KC_SPACE, setMounted);
    Joystick::registerGlobalCallback(joystickState::JS_A, setMounted);

    // Go back to menu
    auto const goBackToMenu([this](bool b, size_t i = 0) {
      if (!b)
      {
	if (uiPause.getOverlay()->isVisible()) {
	  unpauseScene();
	}
	else {
	  pauseScene();
	}
      }
    });
    Keyboard::getKeyboard().registerCallback(OIS::KC_ESCAPE, goBackToMenu);
    Joystick::registerGlobalCallback(joystickState::JS_START, goBackToMenu);
  }
}

void LevelScene::setTerrain(Terrain const &terrain)
{
  for (unsigned int i(0); i < 100; ++i)
  {
    for (unsigned int j(0); j < 100; ++j)
    {
      if (terrain.getTile({ i, j }).isSolid)
      {
	Ogre::SceneNode *wallNode(terrainNode->createChildSceneNode());
	Ogre::Entity* wall(wallNode->getCreator()->createEntity("WallMesh"));

	wall->setCastShadows(true);
	wallNode->attachObject(wall);
	wallNode->setPosition(static_cast<Ogre::Real>(i), 0.0f, static_cast<Ogre::Real>(j));
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
    Vect<3u, double> start{ 0.0, 0.0, 0.0 };
    Vect<3u, double> up{ 0.0, 1.0, 0.0 };
    Vect<3u, double> right{ 0.0, 0.0, 1.0 };

    for (unsigned int i(0); i < 3; ++i)
    {
      for (Vect<2u, double> const &coef : { Vect<2u, double>(0, 0), Vect<2u, double>(1, 0),
	    Vect<2u, double>(0, 1), Vect<2u, double>(1, 1) })
      {
	Vect<3u, double> const pos((start + right * coef[0] + up * coef[1]) * dim);

	obj.position(
	  static_cast<Ogre::Real>(pos[0]),
	  static_cast<Ogre::Real>(pos[1]),
	  static_cast<Ogre::Real>(pos[2])
	);
	obj.textureCoord(
	  static_cast<Ogre::Real>(coef[0]),
	  static_cast<Ogre::Real>(coef[1])
	);
      }
      start = start + right;
      right = { right[2], 0, -right[0] };

      obj.triangle(offset, offset + 1, offset + 3);
      obj.triangle(offset, offset + 3, offset + 2);
      offset += 4;
    }
  }
  { // make the roof
    Vect<3u, double> start{ 0.0, 1.0, 0.0 };
    Vect<3u, double> up{ 0.0, 0.0, 1.0 };
    Vect<3u, double> right{ 1.0, 0.0, 0.0 };

    for (Vect<2u, double> const &coef : {
	Vect<2u, double>(0, 0), Vect<2u, double>(1, 0),
	  Vect<2u, double>(0, 1), Vect<2u, double>(1, 1) })
    {
      Vect<3u, double> const pos((start + right * coef[0] + up * coef[1]) * dim);

      obj.position(
	static_cast<Ogre::Real>(pos[0]),
	static_cast<Ogre::Real>(pos[1]),
	static_cast<Ogre::Real>(pos[2])
      );
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

void LevelScene::pauseScene(void) {
  logicThread->pause();
  inPause = true;
  uiPause.setUIVisible(true);
  resetSceneCallbacks();
}

void LevelScene::unpauseScene(void) {
  logicThread->unpause();
  inPause = false;
  uiPause.setUIVisible(false);
  resetSceneCallbacks();
}
