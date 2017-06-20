#ifndef ENTITY_FACTORY_HPP
# define ENTITY_FACTORY_HPP

# include "Skins.hpp"

class Renderer;
class Entity;
class AnimatedEntity;
class ParticleEffect;

class EntityFactory
{
private:
  Renderer &renderer;

public:
  constexpr EntityFactory(Renderer &renderer)
    : renderer(renderer)
  {}

  Entity spawnOgreHead(void);
  Entity spawnProjectile(unsigned int porjectileType);
  AnimatedEntity spawnHero(Skins::Skin);
  

  template<typename... Args>
  auto spawnArcher(Args&&... args) -> decltype(spawnHero(std::forward<Args>(args)...)) {
    return spawnHero(std::forward<Args>(args)...);
  }

  template<typename... Args>
  auto spawnWarrior(Args&&... args) -> decltype(spawnHero(std::forward<Args>(args)...)) {
    return spawnHero(std::forward<Args>(args)...);
  }

  template<typename... Args>
  auto spawnMage(Args&&... args) -> decltype(spawnHero(std::forward<Args>(args)...)) {
    return spawnHero(std::forward<Args>(args)...);
  }

  template<typename... Args>
  auto spawnTank(Args&&... args) -> decltype(spawnHero(std::forward<Args>(args)...)) {
    return spawnHero(std::forward<Args>(args)...);
  }

  AnimatedEntity spawnEnemy();
  ParticleEffect createParticleSystem(std::string temp);
};

#endif
