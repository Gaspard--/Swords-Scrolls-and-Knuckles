//
// Scene.cpp for  in /home/grange_c/rendu/indie/source
//
// Made by Benjamin Grange
// Login   <grange_c@epitech.net>
//
// Started on  Fri May 12 12:00:28 2017 Benjamin Grange
// Last update Fri May 12 12:00:28 2017 Benjamin Grange
//

#include "Scene.hpp"
#include "Game.hpp"

Scene::Scene(void)
  : _renderer(Game::getSingleton().getRenderer())
{}

void Scene::load(void)
{}

void Scene::unload(void)
{}
