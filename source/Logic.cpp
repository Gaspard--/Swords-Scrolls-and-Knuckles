#include <algorithm>
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

  auto const updateElements([this](auto &elements)
			    {
			      for (auto &element : elements)
				{
				  element.update(*this);
				  gameState.terrain.correctFixture(element);
				}
			    });

  updateElements(gameState.players);
  updateElements(gameState.enemies);
  for (auto &projectile : gameState.projectiles)
    {
      projectile.update(*this);
      gameState.terrain.correctFixture(projectile, Physics::BounceResponse{0.9});
    }
  if (!(rand() % 15))
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
			   player.knockback((player.pos - enemy.pos).normalized() * 0.1, 5);
			 });
  Physics::collisionTest(gameState.projectiles.begin(), gameState.projectiles.end(),
			 gameState.enemies.begin(), gameState.enemies.end(),
			 [](auto &projectile, auto &enemy){
			   enemy.knockback(projectile.speed.normalized() * 0.1, 5);
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
  for (unsigned int i(0); i != 2; ++i) // TODO: obviously players should be passed as parameter or something.
    gameState.players.emplace_back(0.5, Vect<2u, double>{i, i});
  levelScene.setTerrain(gameState.terrain);
  enemies.add([this](){
      return entityFactory.spawnEnemy();
    }, 0.5, Vect<2u, double>{7.5, 7.5});
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
  projectiles.forEach([](Entity &entity, Projectile &projectile)
		      {
			entity.setPosition(static_cast<Ogre::Real>(projectile.pos[0]), 0.f, static_cast<Ogre::Real>(projectile.pos[1]));
		      });
  auto const updateControllableEntity([](AnimatedEntity &animatedEntity, Controllable &controllable){
      animatedEntity.getEntity().setDirection(controllable.getDir());
      animatedEntity.getEntity().setPosition(
	static_cast<Ogre::Real>(controllable.pos[0]),
	animatedEntity.isMounted(), // Put the controllable a bit higher when he's on his mount.
	static_cast<Ogre::Real>(controllable.pos[1])
      );
    });
  enemies.forEach([updateControllableEntity](AnimatedEntity &animatedEntity, Enemy &enemy)
		  {
		    updateControllableEntity(animatedEntity, enemy);
		  });

  for (unsigned int i(0); i != gameState.players.size(); ++i)
    {
      AnimatedEntity &animatedEntity(playerEntities[i]);
      Player &player(gameState.players[i]);

      updateControllableEntity(animatedEntity, player);
      if (player.isWalking())
      {
	if (animatedEntity.isMounted())
	{
	  animatedEntity.setMainAnimation(Animations::Controllable::WALK_RIDE);
	  animatedEntity.getMount()->setMainAnimation(Animations::Controllable::WALK);
	}
	else
	  animatedEntity.setMainAnimation(Animations::Controllable::WALK);
      }
      else
      {
	if (animatedEntity.isMounted())
	{
	  animatedEntity.setMainAnimation(Animations::Controllable::STAND_RIDE);
	  animatedEntity.getMount()->setMainAnimation(Animations::Controllable::STAND);
	}
	else
	  animatedEntity.setMainAnimation(Animations::Controllable::STAND);
      }
      animatedEntity.updateAnimations(static_cast<Ogre::Real>(updatesSinceLastFrame * (1.0f / 120.0f)));
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
  // gameState.players[2].setInput(p2 * 0.03);

  calculateCamera(levelScene);

  updatesSinceLastFrame = 0;
}

void Logic::calculateCamera(LevelScene &levelScene)
{
  constexpr Ogre::Real const angle(180 - 60 / 2);
  Ogre::Real const tanAngle(tan(angle));
  constexpr Ogre::Real const angleUp(180 - 80 / 2);
  Ogre::Real const tanAngleUp(tan(angleUp));
  constexpr Ogre::Real const yMax(20.f);
  Ogre::Vector3 const cameraPos(levelScene.cameraNode->getPosition());
  Ogre::Vector3 cameraDest;

  auto const minmax_x(std::minmax_element(gameState.players.cbegin(),
				    gameState.players.cend(),
				    [](auto const &p1, auto const&p2) {
				      return p1.getPos()[0] < p2.getPos()[0];
				    }));
  auto const leftVecX(Ogre::Vector3{minmax_x.first->getPos()[0], 0,
    minmax_x.first->getPos()[1]} - cameraPos);
  auto const rightVecX(Ogre::Vector3{minmax_x.second->getPos()[0], 0,
    minmax_x.first->getPos()[1]} - cameraPos);
  auto const midVecX((rightVecX - leftVecX) / 2);

  auto const minmax_z(std::minmax_element(gameState.players.cbegin(),
					  gameState.players.cend(),
					  [](auto const &p1, auto const &p2) {
					    return p1.getPos()[1] < p2.getPos()[1];
					  }));
  auto const leftVecZ(Ogre::Vector3{minmax_z.first->getPos()[1], 0,
    minmax_z.first->getPos()[1]} - cameraPos);
  auto const rightVecZ(Ogre::Vector3{minmax_z.second->getPos()[1], 0,
    minmax_z.first->getPos()[1]} - cameraPos);
  auto const midVecZ((rightVecZ - leftVecZ) / 2);

  Ogre::Real const yxpos((-tanAngle * (midVecX.length()) + 10) * 1.5f);
  Ogre::Real const yzpos((-tanAngleUp * (midVecZ.length()) + 10) * 0.8f);

  cameraDest.x = minmax_x.first->getPos()[0]
    + (minmax_x.second->getPos()[0] - minmax_x.first->getPos()[0]) / 2.f;
  cameraDest.y = clamp(std::max(yxpos, yzpos), 0.0f, yMax);
  cameraDest.z = (minmax_z.first->getPos()[1]
		  + (minmax_z.second->getPos()[1] - minmax_z.first->getPos()[1]) / 2.f)
    + 0.5f * cameraDest.y;

  levelScene.cameraNode->setPosition(cameraPos.x + (cameraDest.x - cameraPos.x) / 10,
				     cameraPos.y + (cameraDest.y - cameraPos.y) / 10,
				     cameraPos.z + (cameraDest.z - cameraPos.z) / 10);

}
