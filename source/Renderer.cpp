//
// Renderer.cpp for  in /home/grange_c/rendu/indie/source
//
// Made by Benjamin Grange
// Login   <grange_c@epitech.net>
//
// Started on  Fri May 12 18:41:42 2017 Benjamin Grange
// Last update Fri May 12 18:41:42 2017 Benjamin Grange
//

#include "Renderer.hpp"
#include "Game.hpp"

Renderer::Renderer(Game &game)
  : _game(game)
  , _scenemgr(game.getRoot().createSceneManager(Ogre::ST_GENERIC))
  , _camera(_scenemgr->createCamera("MainCamera"))
{
  _camera->setPosition(0, 0, 80);
  _camera->lookAt(0, 0, -3000);
  _camera->setNearClipDistance(5);
  _viewport.reset(_game.getWindow().addViewport(_camera.get()));
  _viewport->setBackgroundColour(Ogre::ColourValue(1.0, 0.0, 0.0)); // red
  _camera->setAspectRatio(Ogre::Real(_viewport->getActualWidth()) /
			  Ogre::Real(_viewport->getActualHeight()));
}

void Renderer::switchScene(Scene *scene)
{
  _scene.reset(scene);
}

Ogre::SceneManager &Renderer::getSceneManager(void)
{
  return (*_scenemgr);
}

Ogre::SceneManager const &Renderer::getSceneManager(void) const
{
  return (*_scenemgr);
}
