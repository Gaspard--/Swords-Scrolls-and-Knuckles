#ifndef LOGIC_HPP
# define LOGIC_HPP

#include <mutex>
#include <thread>
#include <chrono>
#include <vector>

#include "GameState.hpp"
#include "ModVector.hpp"
#include "Projectile.hpp"
#include "EntityFactory.hpp"
#include "AudioSource.hpp"

class LevelScene;

class Entity;
class AnimatedEntity;
class Renderer;

class Logic
{
private:
  using Clock = std::conditional<std::chrono::high_resolution_clock::is_steady,
				 std::chrono::high_resolution_clock,
				 std::chrono::steady_clock>::type;

  std::mutex lock;
  std::chrono::time_point<Clock> lastUpdate;
  unsigned int updatesSinceLastFrame;
  bool stop;

  std::vector<AnimatedEntity> &playerEntities;
  ModVector<decltype(GameState::enemies)::value_type, AnimatedEntity> enemies;
  ModVector<decltype(GameState::projectiles)::value_type, Entity> projectiles;

  void calculateCamera(LevelScene &);
  bool tick();
public:
  GameState gameState;
  EntityFactory entityFactory;

  /**
   * Parameter isn't stored, only used for setup.
   */
  Logic(LevelScene &levelScene, Renderer &renderer, std::vector<AnimatedEntity> &playerEntities);

  void spawnOgreHead(Vect<2u, float> pos);
  void run();
  void exit();
  void updateDisplay(LevelScene &);
};

#endif
