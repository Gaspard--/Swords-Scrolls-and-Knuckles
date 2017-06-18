#include <algorithm>
#include <iostream>
#include "Logic.hpp"
#include "Physics.hpp"
#include "LevelScene.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "AudioListener.hpp"

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
				  gameState.terrain.correctFixture
				    (element,
				     [](auto &element, Vect<2u, double> dir)
				     {
				       if (element.isStun())
					 BounceResponse{0.5}(element, dir);
				     });
				}
			    });
  updateElements(gameState.players);
  updateElements(gameState.enemies);
  for (auto &player : gameState.players)
    {
      auto &room(gameState.terrain.getRoom(Vect<2u, unsigned int>(player.pos)));

      player.checkSpells(*this);
      if (!room.mobsSpawned)
	{
	  room.mobsSpawned = true;
	  spawnMobGroup(room);
	  std::cout << "spawning mobs" << std::endl;
	}
    }
  auto const updateProjectile([this](auto &projectiles)
			      {
				for (auto &projectile : projectiles)
				  {
				    projectile.update(*this);
				    gameState.terrain.correctFixture(projectile, [this](auto &projectile, Vect<2u, double> dir)
								     {
								       projectileList[projectile.type].wallResponse(projectile, dir);
								     });
				  }
			      });
  updateProjectile(gameState.projectiles);
  updateProjectile(gameState.enemyProjectiles);
  projectiles.removeIf([](auto const &projectile)
		       {
			 return projectile.shouldBeRemoved();
		       });
  enemyProjectiles.removeIf([](auto const &projectile)
			    {
			      return projectile.shouldBeRemoved();
			    });
  Physics::collisionTest(gameState.players.begin(), gameState.players.end(),
			 gameState.enemies.begin(), gameState.enemies.end(),
			 [](auto &player, auto &enemy){
			   player.knockback((player.pos - enemy.pos).normalized() * 0.1, 5);
			 });
  Physics::collisionTest(gameState.projectiles.begin(), gameState.projectiles.end(),
			 gameState.enemies.begin(), gameState.enemies.end(),
			 [this](auto &projectile, auto &enemy){
			   projectileList[projectile.type].hitEnemy(enemy, projectile);
			 });
  constexpr auto const correctOverlap([](auto &a, auto &b){
      auto const center((a.pos + b.pos) * 0.5);
      auto const overlap((a.pos - b.pos).normalized() * (a.radius + b.radius));

      a.pos = center + overlap * 0.5;
      b.pos = center - overlap * 0.5;
    });
  Physics::collisionTest(gameState.players.begin(), gameState.players.end(), correctOverlap);
  Physics::collisionTest(gameState.enemies.begin(), gameState.enemies.end(), correctOverlap);
  for (auto &enemy : gameState.enemies)
    {
      if (enemy.ai)
	pyBindInstance.execAI[enemy.ai](&pyBindInstance, enemy, pyEvaluate);
    }
  return stop;
}

Logic::Logic(LevelScene &levelScene, Renderer &renderer, std::vector<AnimatedEntity> &playerEntities)
  : stop(false)
  , playerEntities(playerEntities)
  , enemies(gameState.enemies, levelScene.enemies)
  , projectiles(gameState.projectiles, levelScene.projectiles)
  , enemyProjectiles(gameState.projectiles, levelScene.projectiles)
  , entityFactory(renderer)
  , pyEvaluate(gameState.players, gameState.enemies)
  , projectileList{}
  , spellList{}
  , keyboardControllers{
      std::map<unsigned int, OIS::KeyCode>
      {{KBACTION::GO_UP, OIS::KC_Z}, {KBACTION::GO_DOWN, OIS::KC_S},
      {KBACTION::GO_LEFT, OIS::KC_Q}, {KBACTION::GO_RIGHT, OIS::KC_D},
      {KBACTION::SPELL1, OIS::KC_V}, {KBACTION::SPELL2, OIS::KC_B},
      {KBACTION::SPELL3, OIS::KC_N}, {KBACTION::LOCK, OIS::KC_LSHIFT}},
      std::map<unsigned int, OIS::KeyCode>
      {{KBACTION::GO_UP, OIS::KC_O}, {KBACTION::GO_DOWN, OIS::KC_L},
      {KBACTION::GO_LEFT, OIS::KC_K}, {KBACTION::GO_RIGHT, OIS::KC_M},
      {KBACTION::SPELL1, OIS::KC_LEFT}, {KBACTION::SPELL2, OIS::KC_RIGHT},
      {KBACTION::SPELL3, OIS::KC_UP}, {KBACTION::LOCK, OIS::KC_RSHIFT}}}
{
  gameState.terrain.generateLevel(42u); // TODO: something better
  for (unsigned int i(0); i != 3; ++i) // TODO: obviously players should be passed as parameter or something.
    gameState.players.push_back(Player::makeArcher(Vect<2u, double>{(double)i + 5.0, (double)i + 5.0}));
  action.keyboardControlled[&keyboardControllers[0]] = &gameState.players[0];
  action.keyboardControlled[&keyboardControllers[1]] = &gameState.players[1];
  if (Joystick::getJoysticks()[0])
  {
      action.joystickControlled[Joystick::getJoysticks()[0].get()] = &gameState.players[2];
  }
  levelScene.setTerrain(gameState.terrain);
  // for (unsigned int i(0u); i < 10; ++i)
  //   {
  //     enemies.add([this](){
  //       return entityFactory.spawnEnemy();
  //     }, AI::CHASEPLAYER, 100u, 0.5, Vect<2u, double>{7.5, 7.5 + (double)i});
  //     enemies.add([this](){
  //       return entityFactory.spawnEnemy();
  //     }, AI::FLEEPLAYER, 100u, 0.5, Vect<2u, double>{3.0, 3.0 + (double)i});
  //   }
}

void Logic::spawnMobGroup(Terrain::Room &room)
{
  std::clog << "[Logic] Spawning mobs at : " << room.pos << std::endl;
  for (unsigned int i(0u); i < 5; ++i)
    enemies.add([this](){
	return entityFactory.spawnEnemy();
      }, AI::FLEEPLAYER, 100u, 0.5, room.pos + Vect<2u, double>{0, (double)i * 0.1});
}

void Logic::spawnProjectile(Vect<2u, double> pos, Vect<2u, double> speed, unsigned int type)
{
  projectiles.add([this](){
      return entityFactory.spawnOgreHead();
    }, pos, speed, type);
}

void Logic::run()
{
  constexpr std::chrono::microseconds TICK_TIME{1000000 / 120};

  lastUpdate = Clock::now();
  updatesSinceLastFrame = 0;
  while (!tick())
    {
      auto const now(Clock::now());

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
  auto const updateProjectileEntities([this](auto &projectiles){
      projectiles.updateTarget();
      projectiles.forEach([](Entity &entity, Projectile &projectile)
			  {
			    entity.setPosition(static_cast<Ogre::Real>(projectile.pos[0]), 0.f, static_cast<Ogre::Real>(projectile.pos[1]));
			  });
    });
  updateProjectileEntities(projectiles);
  updateProjectileEntities(enemyProjectiles);
  auto const updateControllableEntity([](AnimatedEntity &animatedEntity, Controllable &controllable){
      animatedEntity.getEntity().setDirection(controllable.getDir());
      animatedEntity.getEntity().setPosition(static_cast<Ogre::Real>(controllable.pos[0]),
					     animatedEntity.isMounted(), // Put the controllable a bit higher when he's on his mount.
					     static_cast<Ogre::Real>(controllable.pos[1])
					     );
    });
  enemies.forEach([updateControllableEntity, this](AnimatedEntity &animatedEntity, Enemy &enemy)
		  {
		    updateControllableEntity(animatedEntity, enemy);
		    if (enemy.isWalking())
		      animatedEntity.setMainAnimation(Animations::Controllable::WALK);
		    else if (enemy.isStun())
		      animatedEntity.setMainAnimation(Animations::Controllable::STUN);
		    else
		      animatedEntity.setMainAnimation(Animations::Controllable::STAND);
		    animatedEntity.updateAnimations(static_cast<Ogre::Real>(updatesSinceLastFrame * (1.0f / 120.0f)));
		  });

  for (unsigned int i(0); i != gameState.players.size(); ++i)
    {
      AnimatedEntity &animatedEntity(playerEntities[i]);
      Player &player(gameState.players[i]);

      updateControllableEntity(animatedEntity, player);
      if (player.isWalking())
	{
	  if (!animatedEntity.getEntity().soundMap->at(Sounds::BOYAUX1).isPlaying())
	    animatedEntity.getEntity().soundMap->at(Sounds::BOYAUX1).play();
	  if (animatedEntity.isMounted())
	    {
	      animatedEntity.setMainAnimation(Animations::Controllable::Player::WALK_RIDE);
	      animatedEntity.getMount()->setMainAnimation(Animations::Controllable::WALK);
	    }
	  else
	    animatedEntity.setMainAnimation(Animations::Controllable::WALK);
	}
      else
	{
	  if (animatedEntity.getEntity().soundMap->at(Sounds::BOYAUX1).isPlaying())
	    animatedEntity.getEntity().soundMap->at(Sounds::BOYAUX1).stop();
	  if (animatedEntity.isMounted())
	    {
	      animatedEntity.setMainAnimation(Animations::Controllable::Player::STAND_RIDE);
	      animatedEntity.getMount()->setMainAnimation(Animations::Controllable::STAND);
	    }
	  else
	    animatedEntity.setMainAnimation(Animations::Controllable::STAND);
	}
      animatedEntity.updateAnimations(static_cast<Ogre::Real>(updatesSinceLastFrame * (1.0f / 120.0f)));
    }

  action.update();
  calculateCamera(levelScene);
  levelScene.updateUI(gameState.players);
  updatesSinceLastFrame = 0;
}

void Logic::calculateCamera(LevelScene &levelScene)
{
  constexpr double const angle(180 - 60 / 2);
  double const tanAngle(tan(angle));
  constexpr double const angleUp(180 - 80 / 2);
  double const tanAngleUp(tan(angleUp));
  constexpr double const yMax(20.f);
  Vect<3u, double> const cameraPos(levelScene.cameraNode->getPosition().x,
				   levelScene.cameraNode->getPosition().y,
				   levelScene.cameraNode->getPosition().z);

  auto const minmax_x(std::minmax_element(gameState.players.cbegin(),
					  gameState.players.cend(),
					  [](auto const &p1, auto const &p2) {
					    return p1.getPos()[0] < p2.getPos()[0];
					  }));
  Vect<3u, double> const leftVecX(minmax_x.first->getPos()[0], 0.0, minmax_x.first->getPos()[1]);
  Vect<3u, double> const rightVecX(minmax_x.second->getPos()[0], 0.0, minmax_x.first->getPos()[1]);
  auto const midVecX((rightVecX - leftVecX) / 2 - cameraPos);

  auto const minmax_z(std::minmax_element(gameState.players.cbegin(),
					  gameState.players.cend(),
					  [](auto const &p1, auto const &p2) {
					    return p1.getPos()[1] < p2.getPos()[1];
					  }));
  Vect<3u, double> const leftVecZ(minmax_z.first->getPos()[1], 0.0, minmax_z.first->getPos()[1]);
  Vect<3u, double> const rightVecZ(minmax_z.second->getPos()[1], 0.0, minmax_z.first->getPos()[1]);
  auto const midVecZ((rightVecZ - leftVecZ) / 2 - cameraPos);

  double const yxpos((-tanAngle * (std::sqrt(midVecX.length2())) + 10) * 1.5f);
  double const yzpos((-tanAngleUp * (std::sqrt(midVecZ.length2())) + 10) * 0.8f);

  Vect<3u, double> cameraDest;

  cameraDest[0] = minmax_x.first->getPos()[0]
    + (double)(minmax_x.second->getPos()[0] - minmax_x.first->getPos()[0]) / 2.f;
  cameraDest[1] = clamp(std::max(yxpos, yzpos), 0.0, yMax);
  cameraDest[2] = (double)(minmax_z.first->getPos()[1]+ (minmax_z.second->getPos()[1] - minmax_z.first->getPos()[1]) / 2.f)
    + 0.5f * cameraDest[1];

  cameraDest = cameraPos + (cameraDest - cameraPos) / 10.0;
  levelScene.cameraNode->setPosition((Ogre::Real)cameraDest[0],
				     (Ogre::Real)cameraDest[1],
				     (Ogre::Real)cameraDest[2]);

  AudioListener::setPos(levelScene.cameraNode->getPosition());
}

void Logic::pause(void) {
  lock.lock();
}

void Logic::unpause(void) {
  lock.unlock();
}
