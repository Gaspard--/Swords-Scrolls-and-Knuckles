#ifndef LEVEL_SCENE_HPP
# define LEVEL_SCENE_HPP

#include <vector>
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
  Ogre::SceneNode *terrainNode;

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
  LevelScene(Renderer &);
  virtual ~LevelScene(void) = default;

  static void createWallMesh();
  void setTerrain(Terrain const &);
  virtual bool update(Game &, Ogre::FrameEvent const &) override;
};

#endif
