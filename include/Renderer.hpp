//
// Renderer.hpp for  in /home/grange_c/rendu/indie/include
//
// Made by Benjamin Grange
// Login   <grange_c@epitech.net>
//
// Started on  Fri May 12 18:40:38 2017 Benjamin Grange
// Last update Fri May 12 18:40:38 2017 Benjamin Grange
//

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
    Game &_game;
    Ogre::SceneManager *_scenemgr;
    Ogre::Camera *_camera;
    Ogre::Viewport *_viewport;
    std::unique_ptr<Scene> _scene;

  public:
    Renderer(void);
    Renderer(Game &);
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
};

#endif // !RENDERER_HPP
