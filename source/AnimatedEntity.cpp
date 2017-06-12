#include "AnimatedEntity.hpp"

Entity &AnimatedEntity::getEntity(void)
{
  return (entity);
}

Entity const &AnimatedEntity::getEntity(void) const
{
  return (entity);
}

void AnimatedEntity::setMainAnimation(std::string const &s, bool reset, bool loop)
{
  Ogre::AnimationState *as(entity.getOgre()->getAnimationState(s));

  stopMainAnimation();
  mainAnimation = s;
  as->setEnabled(true);
  as->setTimePosition(as->getTimePosition() * !reset);
}

void AnimatedEntity::stopMainAnimation(void)
{
  Ogre::AnimationState *as(entity.getOgre()->getAnimationState(mainAnimation));

  as->setEnabled(false);
}

void AnimatedEntity::addSubAnimation(std::string const &s, bool reset, bool loop)
{
  Ogre::AnimationState *as(entity.getOgre()->getAnimationState(s));

  as->setEnabled(true);
  as->setLoop(loop);
  as->setTimePosition(as->getTimePosition() * !reset);
}

void AnimatedEntity::removeSubAnimation(std::string const &s)
{
  entity.getOgre()->getAnimationState(s)->setEnabled(false);
}

void AnimatedEntity::updateAnimations(Ogre::Real r)
{
  for (auto &anim : entity.getOgre()->getAllAnimationStates()->getAnimationStateIterator()) {
    anim.second->addTime(r);
  }
}
