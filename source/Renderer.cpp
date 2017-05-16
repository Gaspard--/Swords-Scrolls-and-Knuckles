#include "Renderer.hpp"
#include "Game.hpp"

Renderer::Renderer(void)
  : _scenemgr(Game::getGame().getRoot().createSceneManager(Ogre::ST_GENERIC))
  , _camera(_scenemgr->createCamera("MainCamera"))
  , _viewport(Game::getGame().getWindow().addViewport(_camera))
{
  _scenemgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0)); // Black
  _camera->setAspectRatio(Ogre::Real(_viewport->getActualWidth()) /
			  Ogre::Real(_viewport->getActualHeight()));
}

void Renderer::switchScene(std::unique_ptr<Scene> &&ptr)
{
  if (_scene)
    _scene->unload();
  _scenemgr->clearScene();
  Keyboard::getKeyboard().clearCallbacks();
  std::swap(_scene, ptr);
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
