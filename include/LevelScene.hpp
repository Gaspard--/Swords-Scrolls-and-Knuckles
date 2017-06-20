#ifndef LEVEL_SCENE_HPP
# define LEVEL_SCENE_HPP

#include <vector>
#include <utility>
#include "UIOverlaySelection.hpp"
#include "UIOverlayHUD.hpp"
#include "UIOverlayPause.hpp"
#include "Scene.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"
#include "LogicThread.hpp"
#include "Player.hpp"

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
  std::vector<Entity> enemyProjectiles;

private:
  std::vector<Ogre::Light *> lights;
  // Entity ground;
  LogicThread logicThread;

public:
  LevelScene(void) = delete;
  LevelScene(Renderer &,
    std::vector<std::function<AnimatedEntity(Renderer &)>> const &,
    std::vector<PlayerId> const &,
    std::vector<Gameplays> const &);
  virtual ~LevelScene(void);

  static void createWallMesh();
  static void createGroundMesh();
  void setTerrain(Terrain const &);
  virtual bool update(Game &, Ogre::FrameEvent const &) override;
  virtual void resetSceneCallbacks(Renderer &);

  bool isInPause(void) const;
  void updateUI(std::vector<Player> const &);

  void pauseScene(Renderer &);
  void unpauseScene(Renderer &);
};

#endif // !LEVEL_SCENE_HPP
