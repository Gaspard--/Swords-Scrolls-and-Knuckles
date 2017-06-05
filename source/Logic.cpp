#include <iostream>
#include "Logic.hpp"
#include "LevelScene.hpp"

bool Logic::tick()
{
  std::lock_guard<std::mutex> const lock_guard(lock);

  for (auto &player : gameState.players)
    player.update(*this);
  for (auto &enemy : gameState.enemies)
    enemy.update(*this);
  for (auto &projectile : gameState.projectiles)
    projectile.update(*this);

  if (!(rand() % 120))
    {
      projectiles.add([this](){
	  return entityFactory.spawnOgreHead();
	}, Vect<2u, double>{0.0, 0.0}, Vect<2u, double>{(rand() % 10), (rand() % 10)} * 0.1);
    }
  projectiles.removeIf([](auto &projectile)
		       {
			 return projectile.pos[1] > 100;
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
  Physics::collisionTest(gameState.players.begin(), gameState.players.end(),
			 [](auto &playerA, auto &playerB){
			   // TODO: push them appart?
			 });
  Physics::collisionTest(gameState.enemies.begin(), gameState.enemies.end(),
			 [](auto &enemyA, auto &enemyB){
			   // TODO: push them appart?
			 });
  return stop;
}

Logic::Logic(LevelScene &levelScene, Renderer &renderer)
  : stop(false)
  , players(gameState.players, levelScene.players)
  , enemies(gameState.enemies, levelScene.enemies)
  , projectiles(gameState.projectiles, levelScene.projectiles)
  , entityFactory(renderer)
{
  players.add([this]()
	      {
		return entityFactory.spawnIllidan();
	      }, 1.0, Vect<2u, double>{0.0, -10.0});
}

void Logic::run()
{
  constexpr std::chrono::microseconds TICK_TIME{1000000 / 120};

  lastUpdate = Clock::now();
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
	{
	  std::this_thread::sleep_for(lastUpdate - now);
	}
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

  players.updateTarget();
  enemies.updateTarget();
  projectiles.updateTarget();
  players.forEach([](AnimatedEntity &animatedEntity, Player &player)
		  {
		    animatedEntity.getEntity().setPosition(player.pos[0], 50, player.pos[1]);
		  });
  enemies.forEach([](AnimatedEntity &animatedEntity, Enemy &enemy)
		 {
		   animatedEntity.getEntity().setPosition(enemy.pos[0], 50, enemy.pos[1]);
		 });
  projectiles.forEach([](Entity &entity, Projectile &projectile)
		      {
			entity.setPosition(projectile.pos[0], 50, projectile.pos[1]);
		      });
}
