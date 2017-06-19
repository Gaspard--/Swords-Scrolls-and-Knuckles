#include <algorithm>
#include <iostream>
#include "UIOverlaySelection.hpp"
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
  updateElements(gameState.enemies);
  for (auto &enemy : gameState.enemies)
    {
      if (enemy.shouldBeRemoved())
	{
	  auto drop((updatesSinceLastFrame & 1) ? ProjectileType::GOLD : (updatesSinceLastFrame & 3) ? ProjectileType::HEAL : ProjectileType::COOLDOWN_RESET);

	  enemyProjectiles.add([this, drop](){
	      return entityFactory.spawnProjectile(drop);
	    }, enemy.pos, Vect<2u, double>{0.0, 0.0}, drop, 0.5);
	}
    }
  updateElements(gameState.players);
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
  auto const updateProjectile([this](auto &projectiles) {
      for (auto &projectile : projectiles)
	{
	  projectile.update(*this);
	  gameState.terrain.correctFixture(projectile,
					   [this](auto &projectile, Vect<2u, double> dir) {
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
  enemies.removeIf([](auto const &projectile)
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
  Physics::collisionTest(gameState.enemyProjectiles.begin(), gameState.enemyProjectiles.end(),
			 gameState.players.begin(), gameState.players.end(),
			 [this](auto &enemyProjectile, auto &player){
			   if (enemyProjectile.type == ProjectileType::COOLDOWN_RESET)
			     player.resetCooldowns();
			   else if (enemyProjectile.type == ProjectileType::GOLD)
			     player.addGold(99);
			   projectileList[enemyProjectile.type].hitEnemy(player, enemyProjectile);
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

Logic::Logic(LevelScene &levelScene, Renderer &renderer, std::vector<AnimatedEntity> &playerEntities, std::vector<PlayerId> const &vec, std::vector<Gameplays> const &gp)
  : stop(false)
  , playerEntities(playerEntities)
  , enemies(gameState.enemies, levelScene.enemies)
  , projectiles(gameState.projectiles, levelScene.projectiles)
  , enemyProjectiles(gameState.enemyProjectiles, levelScene.enemyProjectiles)
  , entityFactory(renderer)
  , pyEvaluate(gameState.players, gameState.enemies)
  , projectileList{}
  , spellList{}
  , keyboardControllers{
      std::map<unsigned int, OIS::KeyCode>
#if defined OIS_WIN32_PLATFORM
      { {KBACTION::GO_UP, OIS::KC_W}, {KBACTION::GO_DOWN, OIS::KC_S},
      {KBACTION::GO_LEFT, OIS::KC_A}, {KBACTION::GO_RIGHT, OIS::KC_D},
      {KBACTION::SPELL1, OIS::KC_V}, {KBACTION::SPELL2, OIS::KC_B},
      {KBACTION::SPELL3, OIS::KC_N}, {KBACTION::LOCK, OIS::KC_LSHIFT},
      {KBACTION::MOUNT, OIS::KC_Z}},
#else
      {{KBACTION::GO_UP, OIS::KC_Z}, {KBACTION::GO_DOWN, OIS::KC_S},
      {KBACTION::GO_LEFT, OIS::KC_Q}, {KBACTION::GO_RIGHT, OIS::KC_D},
      {KBACTION::SPELL1, OIS::KC_V}, {KBACTION::SPELL2, OIS::KC_B},
      {KBACTION::SPELL3, OIS::KC_N}, {KBACTION::LOCK, OIS::KC_LSHIFT},
      {KBACTION::MOUNT, OIS::KC_W}},
#endif // defined OIS_WIN32_PLATFORM
      std::map<unsigned int, OIS::KeyCode>
#if defined OIS_WIN32_PLATFORM
      { {KBACTION::GO_UP, OIS::KC_O}, {KBACTION::GO_DOWN, OIS::KC_L},
      {KBACTION::GO_LEFT, OIS::KC_K}, {KBACTION::GO_RIGHT, OIS::KC_SEMICOLON},
      {KBACTION::SPELL1, OIS::KC_LEFT}, {KBACTION::SPELL2, OIS::KC_RIGHT},
      {KBACTION::SPELL3, OIS::KC_UP}, {KBACTION::LOCK, OIS::KC_RSHIFT},
      {KBACTION::MOUNT, OIS::KC_DOWN}} }
#else
      { {KBACTION::GO_UP, OIS::KC_O}, {KBACTION::GO_DOWN, OIS::KC_L},
      {KBACTION::GO_LEFT, OIS::KC_K}, {KBACTION::GO_RIGHT, OIS::KC_M},
      {KBACTION::SPELL1, OIS::KC_LEFT}, {KBACTION::SPELL2, OIS::KC_RIGHT},
      {KBACTION::SPELL3, OIS::KC_UP}, {KBACTION::LOCK, OIS::KC_RSHIFT},
      {KBACTION::MOUNT, OIS::KC_DOWN}}}
#endif // defined OIS_WIN32_PLATFORM
{
  gameState.terrain.generateLevel(42u); // TODO: something better
  for (size_t i = 0; i < vec.size(); i++) {
    gameState.players.push_back(Player::makePlayer(Vect<2u, double>{(double)i + 8.0, (double)(i % 2) + 8.0}, vec[i]));
  }
  size_t kb = 0;
  size_t js = 0;
  for (size_t i = 0; i < gp.size(); i++) {
    if (gp[i] == Gameplays::KEYBOARD) {
      action.keyboardControlled[&keyboardControllers[kb]] = &gameState.players[i];
      kb++;
    }
    else if (gp[i] == Gameplays::JOYSTICK && Joystick::getJoysticks()[js]) {
      action.joystickControlled[Joystick::getJoysticks()[js].get()] = &gameState.players[i];
      js++;
    }
    else if (gp[i] == Gameplays::IA) {
      // TODO
    }
  }
  levelScene.setTerrain(gameState.terrain);
}

void Logic::spawnMobGroup(Terrain::Room &room)
{
  std::clog << "[Logic] Spawning mobs at : " << room.pos << std::endl;
  for (unsigned int i(0u); i < 5; ++i)
    enemies.add([this](){
	return entityFactory.spawnEnemy();
      }, AI::FLEEPLAYER, 100u, 0.5, room.pos + Vect<2u, double>{0., (double)i * 0.1});
}

void Logic::spawnProjectile(Vect<2u, double> pos, Vect<2u, double> speed, unsigned int type, double size, unsigned int timeLeft)
{
  projectiles.add([this](){
      return entityFactory.spawnOgreHead();
    }, pos, speed, type, size, timeLeft);
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
			    if (projectile.doSpin())
			      entity.setDirection(Vect<2u, float>((float)std::cos(projectile.timeLeft * 0.01), (float)std::sin(projectile.timeLeft * 0.01)));
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
		    if (enemy.isDead())
		      animatedEntity.setMainAnimation(Animations::Controllable::Enemy::DEATH, 0.04f, false);
		    else if (enemy.isWalking())
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
      bool otherMainAnimation{false};

      switch (static_cast<PlayerId>(player.getId()))
	{
	case PlayerId::ARCHER:
	  break;
	case PlayerId::MAGE:
	  break;
	case PlayerId::TANK:
	  break;
	case PlayerId::WARRIOR:
	  break;
	}

      updateControllableEntity(animatedEntity, player);
      if (player.isMounted() != animatedEntity.isMounted()) {
	animatedEntity.setMounted(player.isMounted());
      }
      if (player.isWalking())
	{
	  if (!animatedEntity.getEntity().soundMap->at(Sounds::FOOTSTEPS).isPlaying())
	    animatedEntity.getEntity().soundMap->at(Sounds::FOOTSTEPS).play();
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
	  if (animatedEntity.getEntity().soundMap->at(Sounds::FOOTSTEPS).isPlaying())
	    animatedEntity.getEntity().soundMap->at(Sounds::FOOTSTEPS).stop();
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
