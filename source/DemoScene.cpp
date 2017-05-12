#include "DemoScene.hpp"
#include "Game.hpp"

DemoScene::DemoScene(Game &game)
  : Scene(game)
{
  std::clog << "Loading demo scene" << std::endl;
  Ogre::Entity *ogreEntity = _renderer.getSceneManager().createEntity("ogrehead.mesh");

  Ogre::SceneNode *ogreNode = _renderer.getSceneManager().getRootSceneNode()->createChildSceneNode();

  ogreNode->attachObject(ogreEntity);

  _renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

  Ogre::Light *light = _renderer.getSceneManager().createLight("MainLight");
  light->setPosition(20, 80, 50);

  std::clog << "End loading" << std::endl;
}
