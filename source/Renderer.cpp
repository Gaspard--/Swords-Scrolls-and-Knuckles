#include "Renderer.hpp"
#include "Game.hpp"

Renderer::Renderer(Game &game)
  : scenemgr(game.getRoot().createSceneManager(Ogre::ST_GENERIC))
  , camera(scenemgr->createCamera("MainCamera"))
  , viewport(game.getWindow().addViewport(camera))
{
  scenemgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
  viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0)); // Black
  camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) /
			  Ogre::Real(viewport->getActualHeight()));
}

void Renderer::switchScene(Game &game, std::unique_ptr<Scene> &&ptr)
{
  Keyboard::getKeyboard().clearCallbacks();
  if (scene)
    scene->unload(game);
  scenemgr->clearScene();
  std::swap(scene, ptr);
  if (scene)
    scene->load(game);
}

Ogre::SceneManager &Renderer::getSceneManager(void)
{
  return (*scenemgr);
}

Ogre::SceneManager const &Renderer::getSceneManager(void) const
{
  return (*scenemgr);
}

Ogre::Camera &Renderer::getCamera(void)
{
  return (*camera);
}

Ogre::Camera const &Renderer::getCamera(void) const
{
  return (*camera);
}

std::unique_ptr<Scene> const &Renderer::getScene(void) const {
  return (scene);
}
