#ifndef RENDERER_HPP
# define RENDERER_HPP

# include <memory>
# include <functional>
# include <OgreSceneManager.h>
# include <OgreCamera.h>
# include <OgreViewport.h>
# include <Overlay/OgreOverlaySystem.h>
# include "Mouse.hpp"
# include "Joystick.hpp"
# include "Keyboard.hpp"
# include "Scene.hpp"

class Renderer
{
public:
  class SceneSwitcherException; // Defined later

private:
  Ogre::SceneManager *scenemgr;
  Ogre::Camera *camera;
  Ogre::Viewport *viewport;
  std::unique_ptr<Scene> scene;

public:
  Renderer(void) = delete;
  Renderer(Game &);
  Renderer(Renderer const &) = delete;
  Renderer(Renderer &&) = delete;
  ~Renderer(void) = default;
  Renderer &operator=(Renderer const &) = delete;
  Renderer &operator=(Renderer &&) = delete;

  void doSwitchScene(SceneSwitcherException const &se)
  {
    Keyboard::getKeyboard().clearCallbacks();
    Mouse::getMouse().clearCallbacks();
    for (auto const &js : Joystick::getJoysticks()) {
      if (js != nullptr)
	js->clearCallbacks();
    }
    scene.reset(nullptr);
    scenemgr->clearScene();
    scene.reset(se.switchScene());
    scene->resetSceneCallbacks(*this);
  }

  /// Switch the current scene to the given one.
  template<class SCENE_LOADER>
  void switchScene(SCENE_LOADER &&sceneLoader)
  {
    throw SceneSwitcherException(sceneLoader);
  }

  /// Returns the scene manager
  Ogre::SceneManager &getSceneManager(void);
  Ogre::SceneManager const &getSceneManager(void) const;

  /// Returns the camera
  Ogre::Camera &getCamera(void);
  Ogre::Camera const &getCamera(void) const;


  /// Returns the current scene
  std::unique_ptr<Scene> const & getScene(void) const;

  // Scene switching exceptions

  class SceneSwitcherException : public std::exception {
  private:
    std::function<Scene *(void)> fn;
    public:
      SceneSwitcherException(std::function<Scene *(void)> const &fn)
	: std::exception()
	, fn(fn)
      {}

      Scene *switchScene(void) const
      {
	return (fn());
      }
  };
};

#endif // !RENDERER_HPP
