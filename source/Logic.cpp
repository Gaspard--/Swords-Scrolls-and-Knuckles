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
  updateElements(gameState.projectiles);
  if (!(rand() % 10))
    {
      projectiles.add([this](){
	  return entityFactory.spawnOgreHead();
	}, Vect<2u, double>{5.0, 5.0}, Vect<2u, double>{(rand() % 100 + 1), (rand() % 100 + 1)} * 0.0005);
    }
  projectiles.removeIf([](auto const &projectile)
		       {
			 return projectile.pos[0] > 20.0 || projectile.pos[1] > 20.0;
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
  for (unsigned int i(0); i != 2u; ++i) // TODO: obviously players should be passed as parameter or something.
    gameState.players.emplace_back(0.5, Vect<2u, double>{5.0, 4.0 + i});
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
		    animatedEntity.getEntity().setPosition(enemy.pos[0], 0, enemy.pos[1]);
		  });
  projectiles.forEach([](Entity &entity, Projectile &projectile)
		      {
			entity.setPosition(projectile.pos[0], 0, projectile.pos[1]);
		      });
  /*
    gameState.players[0].setInput(p0 * 3.0);
    gameState.players[1].setInput(p1 * 3.0);
    gameState.players[2].setInput(p2 * 3.0);
    std::cout << "p0 : " << gameState.players[0].getPos() << '\n'
      << "p1 : " << gameState.players[1].getPos() << '\n'
      << "p2 : " << gameState.players[2].getPos() << std::endl;

    if (mmx.second - mmx.first > 1500 + levelScene.cameraNode->getPosition().y)
      {
	y += mmx.second - mmx.first - 1500 + levelScene.cameraNode->getPosition().y;
      }

    std::cout << "min : " << mmx.first << ", max : " << mmx.second << std::endl;

      {
	#include <OgreAxisAlignedBox.h>

      }*/


  for (unsigned int i(0); i != gameState.players.size(); ++i)
    {
      AnimatedEntity &animatedEntity(playerEntities[i]);
      Player &player(gameState.players[i]);

      animatedEntity.getEntity().setDirection(player.getDir());

      animatedEntity.getEntity().setPosition(player.pos[0], 0, player.pos[1]);
      if (player.isWalking())
	{
	  animatedEntity.addAnimation("Move", false, true);
	  animatedEntity.removeAnimation("Stand");
	}
      else
	{
	  animatedEntity.removeAnimation("Move");
	  animatedEntity.addAnimation("Stand", false, true);
	}
      animatedEntity.updateAnimations(updatesSinceLastFrame * (1.0 / 120.0));
    }
  Vect<2u, double> p0{0.0, 0.0};
  Vect<2u, double> p1{0.0, 0.0};
  Vect<2u, double> p2{0.0, 0.0};

  if (Keyboard::getKeys()[OIS::KC_Z]) {
    p0 += {0.0, -1.0};
  }
  if (Keyboard::getKeys()[OIS::KC_Q]) {
    p0 += {-1.0, 0.0};
  }
  if (Keyboard::getKeys()[OIS::KC_S]) {
    p0 += {0.0, 1.0};
  }
  if (Keyboard::getKeys()[OIS::KC_D]) {
    p0 += {1.0, 0.0};
  }

  if (Keyboard::getKeys()[OIS::KC_I]) {
    p1 += {0.0, -1.0};
  }
  if (Keyboard::getKeys()[OIS::KC_J]) {
    p1 += {-1.0, 0.0};
  }
  if (Keyboard::getKeys()[OIS::KC_K]) {
    p1 += {0.0, 1.0};
  }
  if (Keyboard::getKeys()[OIS::KC_L]) {
    p1 += {1.0, 0.0};
  }

     if (Keyboard::getKeys()[OIS::KC_UP]) {
     p2 += {0.0, -1.0};
     }
     if (Keyboard::getKeys()[OIS::KC_LEFT]) {
     p2 += {-1.0, 0.0};
     }
     if (Keyboard::getKeys()[OIS::KC_DOWN]) {
     p2 += {0.0, 1.0};
     }
     if (Keyboard::getKeys()[OIS::KC_RIGHT]) {
     p2 += {1.0, 0.0};
     }

  gameState.players[0].setInput(p0 * 0.03);
  gameState.players[1].setInput(p1 * 0.03);
    Ogre::Real x(0.0);
    Ogre::Real y(levelScene.cameraNode->getPosition().y);

    auto minmax_x(std::minmax_element(gameState.players.cbegin(),
				      gameState.players.cend(),
				      [](auto &p1, auto &p2) {
					return p1.getPos()[0] < p2.getPos()[0];
				      }));
    auto mmx = std::make_pair(minmax_x.first->getPos()[0], minmax_x.second->getPos()[0]);
    Ogre::Real z(0.0);
    std::for_each(gameState.players.cbegin(), gameState.players.cend(),
		  [&x, &z](auto &p) {
		    x += p.getPos()[0];
		    z += p.getPos()[1];
		  });
    x /= (float)gameState.players.size();
    z = z / (float)gameState.players.size() + 0.5 * levelScene.cameraNode->getPosition().y;

    levelScene.cameraNode->setPosition(x, y, z);
  updatesSinceLastFrame = 0;
}
