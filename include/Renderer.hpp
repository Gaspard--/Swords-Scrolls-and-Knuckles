#ifndef RENDERER_HPP
# define RENDERER_HPP

# include <memory>
# include <OgreSceneManager.h>
# include <OgreCamera.h>
# include <OgreViewport.h>
# include "Scene.hpp"

class Game;

class Renderer
{
  private:
    Ogre::SceneManager *_scenemgr;
    Ogre::Camera *_camera;
    Ogre::Viewport *_viewport;
    std::unique_ptr<Scene> _scene;

  public:
    Renderer(void);
    Renderer(Renderer const &) = delete;
    Renderer(Renderer &&) = delete;
    ~Renderer(void) = default;
    Renderer &operator=(Renderer const &) = delete;
    Renderer &operator=(Renderer &&) = delete;

    /// Switch the current scene to the given one.
    void switchScene(std::unique_ptr<Scene> &&);

    /// Returns the scene manager
    Ogre::SceneManager &getSceneManager(void);
    Ogre::SceneManager const &getSceneManager(void) const;

    /// Returns the camera
    Ogre::Camera &getCamera(void);
    Ogre::Camera const &getCamera(void) const;
};

#endif // !RENDERER_HPP
