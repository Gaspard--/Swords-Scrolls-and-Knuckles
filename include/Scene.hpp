#ifndef SCENE_HPP
# define SCENE_HPP

# include <OgreFrameListener.h>
# include "Joystick.hpp"

class Game;

class Scene
{
public:
  /// Used to load all the elements of the new scene
  constexpr Scene(void) = default;
  
  Scene(Scene const &) = delete;
  Scene(Scene &&) = delete;
  Scene &operator=(Scene const &) = delete;
  Scene &operator=(Scene &&) = delete;

  /// Called each frame to update scene logic.
  /// Return value: false to exit the game, true otherwise.
  virtual ~Scene(void) = default;

  virtual bool update(Game &, Ogre::FrameEvent const &);
  virtual void resetSceneCallbacks(void);
};

#endif // !SCENE_HPP
