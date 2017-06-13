#ifndef ENTITY_FACTORY_HPP
# define ENTITY_FACTORY_HPP

# include "Skins.hpp"

class Renderer;
class Entity;
class AnimatedEntity;

class EntityFactory
{
private:
  Renderer &renderer;
public:
  constexpr EntityFactory(Renderer &renderer)
  : renderer(renderer)
  {}

  Entity spawnOgreHead(void);
  AnimatedEntity spawnArcher(Skins::Skin);
};

#endif
