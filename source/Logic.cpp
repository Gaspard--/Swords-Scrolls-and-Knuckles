#include <iostream>
#include "Logic.hpp"
#include "Physics.hpp"
#include "LevelScene.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

// TODO: extract as mush as possible to gameState.
// Logic could be passed as ref for spawning and & so on.
bool Logic::tick()
{
  std::lock_guard<std::mutex> const lock_guard(lock);

  ++updatesSinceLastFrame;

  auto const updateElements([this](auto &fixtures)
			    {
			      for (auto &fixture : fixtures)
				{
				  fixture.update(*this);
				  gameState.terrain.correctFixture(fixture);
				}
			    });

  updateElements(gameState.players);
  updateElements(gameState.enemies);
  for (auto &fixture : gameState.projectiles)
    {
      fixture.update(*this);
      gameState.terrain.correctFixture(fixture, Physics::BounceResponse{1.0});
    }
  if (!(rand() % 10))
    {
      projectiles.add([this](){
	  return entityFactory.spawnOgreHead();
	}, Vect<2u, double>{5.5, 5.5}, Vect<2u, double>{(rand() % 100 + 1), (rand() % 100 + 1)} * 0.0005);
    }
  projectiles.removeIf([](auto const &projectile)
		       {
			 return projectile.pos[0] > 15.0 || projectile.pos[1] > 15.0;
		       });
  Physics::collisionTest(gameState.players.begin(), gameState.players.end(),
			 gameState.enemies.begin(), gameState.enemies.end(),
			 [](auto &player, auto &enemy){
			   enemy.hit(player);
			 });
  Physics::collisionTest(gameState.projectiles.begin(), gameState.projectiles.end(),
			 gameState.enemies.begin(), gameState.enemies.end(),
			 [](auto &projectile, auto &enemy){
			   projectile.hit(enemy);
			 });
  constexpr auto const correctOverlap([](auto &a, auto &b){
      auto const center((a.pos + b.pos) * 0.5);
      auto const overlap((a.pos - b.pos).normalized() * (a.radius + b.radius));

      a.pos = center + overlap * 0.5;
      b.pos = center - overlap * 0.5;
    });
  Physics::collisionTest(gameState.players.begin(), gameState.players.end(), correctOverlap);
  Physics::collisionTest(gameState.enemies.begin(), gameState.enemies.end(), correctOverlap);
  return stop;
}

Logic::Logic(LevelScene &levelScene, Renderer &renderer, std::vector<AnimatedEntity> &playerEntities)
  : stop(false)
  , playerEntities(playerEntities)
  , enemies(gameState.enemies, levelScene.enemies)
  , projectiles(gameState.projectiles, levelScene.projectiles)
  , entityFactory(renderer)
{
  for (unsigned int i(0); i != 1u; ++i) // TODO: obviously players should be passed as parameter or something.
    gameState.players.emplace_back(0.5, Vect<2u, double>{5.0, 5.0});
  levelScene.setTerrain(gameState.terrain);
}

void Logic::run()
{
  constexpr std::chrono::microseconds TICK_TIME{1000000 / 120};

  lastUpdate = Clock::now();
  updatesSinceLastFrame = 0;
  while (!tick())
    {
      auto now(Clock::now());

      if (now > lastUpdate + TICK_TIME * 3)
	{
	  lastUpdate = now;
	  continue ;
	}
      lastUpdate += TICK_TIME;
      if (now < lastUpdate)
	std::this_thread::sleep_for(lastUpdate - now);
    }
  std::clog << "[Logic] thread exiting" << std::endl;
}

void Logic::exit()
{
  std::lock_guard<std::mutex> const lock_guard(lock);

  stop = true;
  std::clog << "[Logic] stoping thread" << std::endl;
}

void Logic::updateDisplay(LevelScene &levelScene)
{
  std::lock_guard<std::mutex> const lock_guard(lock);

  enemies.updateTarget();
  projectiles.updateTarget();
  enemies.forEach([](AnimatedEntity &animatedEntity, Enemy &enemy)
		  {
		    animatedEntity.getEntity().setPosition(static_cast<Ogre::Real>(enemy.pos[0]), 0.f, static_cast<Ogre::Real>(enemy.pos[1]));
		  });
  projectiles.forEach([](Entity &entity, Projectile &projectile)
		      {
			entity.setPosition(static_cast<Ogre::Real>(projectile.pos[0]), 0.f, static_cast<Ogre::Real>(projectile.pos[1]));
		      });
  for (unsigned int i(0); i != gameState.players.size(); ++i)
    {
      AnimatedEntity &animatedEntity(playerEntities[i]);
      Player &player(gameState.players[i]);

      animatedEntity.getEntity().setDirection(player.getDir());
      animatedEntity.getEntity().setPosition(static_cast<Ogre::Real>(player.pos[0]), 0.f, static_cast<Ogre::Real>(player.pos[1]));
      if (player.isWalking())
	animatedEntity.setMainAnimation(Animations::WALK);
      else
	animatedEntity.setMainAnimation(Animations::STAND);
      animatedEntity.updateAnimations(static_cast<Ogre::Real>(updatesSinceLastFrame * (1.0f / 120.0f)));
      Vect<2u, double> inputDir{0.0, 0.0};

      if (Keyboard::getKeys()[OIS::KC_Z]) {
	inputDir += {0.0, -1.0};
      }
      if (Keyboard::getKeys()[OIS::KC_Q]) {
	inputDir += {-1.0, 0.0};
      }
      if (Keyboard::getKeys()[OIS::KC_S]) {
	inputDir += {0.0, 1.0};
      }
      if (Keyboard::getKeys()[OIS::KC_D]) {
	inputDir += {1.0, 0.0};
      }
      player.setInput(inputDir * 0.03);
    }
  updatesSinceLastFrame = 0;
}
