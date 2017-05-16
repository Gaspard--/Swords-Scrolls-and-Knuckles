#include "Scene.hpp"
#include "Game.hpp"

Scene::Scene(void)
  : _renderer(Game::getGame().getRenderer())
{}

void Scene::load(void)
{}

void Scene::unload(void)
{}

bool Scene::update(void)
{
  return (true);
}
