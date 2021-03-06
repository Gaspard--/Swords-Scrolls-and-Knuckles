#include "AnimatedEntity.hpp"

Entity &AnimatedEntity::getEntity(void)
{
  return (entity);
}

Entity const &AnimatedEntity::getEntity(void) const
{
  return (entity);
}

void AnimatedEntity::setMainAnimation(std::string const &s, Ogre::Real timer, bool loop)
{
  Ogre::AnimationState *target = entity.getOgre()->getAnimationState(s);

  if (blendTimer <= 0 && targetMainAnimation != target)
  {
    blendTimer = timer;
    blendDuration = timer;
    targetMainAnimation = target;
    targetMainAnimation->setEnabled(true);
    targetMainAnimation->setLoop(loop);
    targetMainAnimation->setWeight(0.f);
    targetMainAnimation->setTimePosition(0.f);
  }
  else if (blendTimer > 0 && target == mainAnimation)
  {
    mainAnimation = targetMainAnimation;
    targetMainAnimation = target;
    blendTimer = blendDuration - blendTimer;
  }
}

void AnimatedEntity::addSubAnimation(std::string const &s, bool reset, bool loop)
{
  Ogre::AnimationState *as(entity.getOgre()->getAnimationState(s));

  as->setLoop(loop);
  as->setWeight(as->getWeight() * !reset + 0.10f * reset);
  as->setTimePosition(as->getTimePosition() * !reset);
  as->setEnabled(true);
}

void AnimatedEntity::stopSubAnimation(std::string const &s)
{
  entity.getOgre()->getAnimationState(s)->setEnabled(false);
}

void AnimatedEntity::updateAnimations(Ogre::Real r)
{
  if (entityMount)
    entityMount->updateAnimations(r);
  if (blendTimer > 0)
  {
    blendTimer -= r;
    if (blendTimer <= 0)
    {
      mainAnimation->setEnabled(false);
      mainAnimation->setWeight(0.f);
      mainAnimation = targetMainAnimation;
      mainAnimation->setEnabled(true);
      mainAnimation->setWeight(1.f);
      blendTimer = 0;
    }
    else
    {
      mainAnimation->setWeight(blendTimer / blendDuration);
      targetMainAnimation->setWeight(1.f - blendTimer / blendDuration);
    }
  }
  for (auto &anim : entity.getOgre()->getAllAnimationStates()->getAnimationStateIterator()) {
    anim.second->addTime(r);
    if (anim.second != mainAnimation && anim.second != targetMainAnimation)
    {
      if (anim.second->getTimePosition() >= anim.second->getLength() && anim.second->getWeight() > 0.01f)
        anim.second->setWeight(anim.second->getWeight() / 1.5f);
      else if (anim.second->getTimePosition() < anim.second->getLength() && anim.second->getWeight() < 1.f)
        anim.second->setWeight(anim.second->getWeight() * 1.5f);
      anim.second->setEnabled(anim.second->getEnabled() * (anim.second->getWeight() > 0.01));
    }
  }
}

void AnimatedEntity::setMount(AnimatedEntity *m)
{
  setMounted(false);
  entityMount.reset(m);
  setMounted(false);
}

void AnimatedEntity::setMounted(bool b)
{
  if (entityMount)
    entityMount->getEntity().getOgre()->setVisible(b);
}

AnimatedEntity *AnimatedEntity::getMount(void)
{
  return (entityMount.get());
}

bool AnimatedEntity::isMounted(void)
{
  return (entityMount && entityMount->getEntity().getOgre()->isVisible());
}
