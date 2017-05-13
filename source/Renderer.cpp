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

Renderer::Renderer(void)
  : _scenemgr(Game::getSingleton().getRoot().createSceneManager(Ogre::ST_GENERIC))
  , _camera(_scenemgr->createCamera("MainCamera"))
  , _viewport(Game::getSingleton().getWindow().addViewport(_camera))
{
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0)); // Black
  _camera->setAspectRatio(Ogre::Real(_viewport->getActualWidth()) /
			  Ogre::Real(_viewport->getActualHeight()));
}

void Renderer::switchScene(std::unique_ptr<Scene> &&ptr)
{
  if (_scene)
    _scene->unload();
  _scenemgr->clearScene();
  _scene = std::move(ptr);
  if (_scene)
    _scene->load();
}

Ogre::SceneManager &Renderer::getSceneManager(void)
{
  return (*_scenemgr);
}

Ogre::SceneManager const &Renderer::getSceneManager(void) const
{
  return (*_scenemgr);
}

Ogre::Camera &Renderer::getCamera(void)
{
  return (*_camera);
}

Ogre::Camera const &Renderer::getCamera(void) const
{
  return (*_camera);
}
