#include "AudioListener.hpp"
#include "Renderer.hpp"
#include "Game.hpp"

Renderer::Renderer(Game &game)
  : scenemgr(game.getRoot().createSceneManager(Ogre::ST_GENERIC))
  , camera(scenemgr->createCamera("MainCamera"))
  , viewport(game.getWindow().addViewport(camera))
{
  scenemgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  scenemgr->setShadowIndexBufferSize(1024);
  scenemgr->addRenderQueueListener(new Ogre::OverlaySystem());

  // viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0)); // Black
  camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) /
    Ogre::Real(viewport->getActualHeight()));
  
  // Options init
  options.emplace_back("FULLSCREEN", true, [&game](bool b) {
    game.getWindow().setFullscreen(b, Game::WIDTH, Game::HEIGHT);
  });
  options.emplace_back("SOUNDS", true, [](bool b) {
    AudioListener::setVolume(static_cast<float>(b));
  });
  options.emplace_back("VSYNC", true, [&game](bool b) {
    game.getWindow().setVSyncEnabled(b);
  });
  options.emplace_back("STENCIL SHADOWS", true, [this](bool b) {
    scenemgr->setShadowTechnique(b ? Ogre::SHADOWTYPE_STENCIL_ADDITIVE : Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);
  });
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

std::vector<Option> &Renderer::getOptions(void)
{
  return (options);
}

std::vector<Option> const &Renderer::getOptions(void) const
{
  return (options);
}
