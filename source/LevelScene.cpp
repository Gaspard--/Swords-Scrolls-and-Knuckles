#include "LevelScene.hpp"

LevelScene::LevelScene(Game &)
{
}

LevelScene::~LevelScene()
{
}

bool LevelScene::update(Game &)
{
  logicThread->updateDisplay(*this);
  return true;
}

