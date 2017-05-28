#include "LevelScene.hpp"

LevelScene::LevelScene(Game &)
{
}

LevelScene::~LevelScene()
{
}

bool LevelScene::update(Game &, Ogre::FrameEvent const &)
{
  logicThread->updateDisplay(*this);
  return true;
}

