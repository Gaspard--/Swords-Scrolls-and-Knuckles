#ifndef LEVEL_SCENE_HPP
# define LEVEL_SCENE_HPP

#include "Scene.hpp"
#include "LogicThread.hpp"

/**
 * Class representation of the ingame scene.
 * This class should handle most basic interactions between game logic
 * and entities.
 * Should NOT be inherited. (ideally)
 */
class LevelScene : public Scene
{
private:
  LogicThread logicThread;
public:
  LevelScene(Game &);

  virtual ~LevelScene(void);

  virtual bool update(Game &, Ogre::FrameEvent const &) override;
};

#endif
