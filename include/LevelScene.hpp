#ifndef LEVEL_SCENE_HPP
# define LEVEL_SCENE_HPP

#include <vector>
#include "UIOverlayHUD.hpp"
#include "UIOverlayPause.hpp"
#include "Scene.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"
#include "LogicThread.hpp"
#include "Music.hpp"

class Terrain;

/**
 * Class representation of the ingame scene.
 * This class should handle most basic interactions between game logic
 * and entities.
 * Should NOT be inherited. (ideally)
 */
class LevelScene : public Scene
{
private:
  UIOverlayHUD uiHUD;
  UIOverlayPause uiPause;
  Ogre::SceneNode *terrainNode;
  bool inPause;

public:
  Ogre::SceneNode *cameraNode;
  std::vector<AnimatedEntity> players;
  std::vector<AnimatedEntity> enemies;
  std::vector<Entity> projectiles;

private:
  std::vector<Ogre::Light *> lights;
  Entity ground;
  LogicThread logicThread;
  // Music music;

public:
  LevelScene(void) = delete;
  LevelScene(Renderer &);
  virtual ~LevelScene(void);

  static void createWallMesh();
  void setTerrain(Terrain const &);
  virtual bool update(Game &, Ogre::FrameEvent const &) override;
  virtual void resetSceneCallbacks(void);

  bool isInPause(void) const;

  void pauseScene(void);
  void unpauseScene(void);
};

#endif // !LEVEL_SCENE_HPP
