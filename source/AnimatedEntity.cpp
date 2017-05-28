#include "AnimatedEntity.hpp"

Entity &AnimatedEntity::getEntity(void)
{
  return (entity);
}

Entity const &AnimatedEntity::getEntity(void) const
{
  return (entity);
}

void AnimatedEntity::stopAnimation(void)
{
  for (auto &anim : entity.getOgre()->getAllAnimationStates()->getAnimationStateIterator()) {
    anim.second->setEnabled(false);
  }
}

void AnimatedEntity::setAnimation(std::string const &s, bool reset, bool loop)
{
  stopAnimation();
  addAnimation(s, reset, loop);
}

void AnimatedEntity::addAnimation(std::string const &s, bool reset, bool loop)
{
  Ogre::AnimationState *as(entity.getOgre()->getAnimationState(s));

  as->setEnabled(true);
  as->setLoop(loop);
  as->setTimePosition(as->getTimePosition() * !reset);
}

void AnimatedEntity::removeAnimation(std::string const &s)
{
  entity.getOgre()->getAnimationState(s)->setEnabled(false);
}

void AnimatedEntity::updateAnimations(Ogre::Real r)
{
  for (auto &anim : entity.getOgre()->getAllAnimationStates()->getAnimationStateIterator()) {
    anim.second->addTime(r);
  }
}
