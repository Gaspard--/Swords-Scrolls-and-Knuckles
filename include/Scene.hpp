//
// Scene.hpp for  in /home/grange_c/rendu/indie/include
//
// Made by Benjamin Grange
// Login   <grange_c@epitech.net>
//
// Started on  Thu May 11 22:50:03 2017 Benjamin Grange
// Last update Thu May 11 22:50:03 2017 Benjamin Grange
//

#ifndef SCENE_HPP
# define SCENE_HPP

class Game;
class Renderer;

class Scene
{
  protected:
    Game &_game;
    Renderer &_renderer;

  public:
    Scene(void) = delete;
    Scene(Game &);
    Scene(Scene const &) = delete;
    Scene(Scene &&) = delete;
    Scene &operator=(Scene const &) = delete;
    Scene &operator=(Scene &&) = delete;
    virtual ~Scene(void) = default;

    virtual void load(void);
    virtual void unload(void);
};

#endif // !SCENE_HPP
