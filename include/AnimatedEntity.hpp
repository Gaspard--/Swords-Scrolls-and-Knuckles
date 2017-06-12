#ifndef ANIMATED_ENTITY_HPP
# define ANIMATED_ENTITY_HPP

# include <map>
# include <vector>
# include <string>
# include <OgreAnimationState.h>
# include "Entity.hpp"
# include "Animations.hpp"

class AnimatedEntity
{
  Entity entity;
  std::string mainAnimation;

public:

  template<class... P>
  AnimatedEntity(P&&... params)
    : entity(std::forward<P>(params)...)
    , mainAnimation(Animations::IDLE)
  {}

  AnimatedEntity(AnimatedEntity const &ae) = delete;
  AnimatedEntity(AnimatedEntity &&ae) = default;

  AnimatedEntity &operator=(AnimatedEntity const &) = delete;
  AnimatedEntity &operator=(AnimatedEntity &&) = default;
  ~AnimatedEntity(void) = default;

  /// Return the entity
  Entity &getEntity(void);
  Entity const &getEntity(void) const;

  /// Set the main animation
  void setMainAnimation(std::string const &s, bool reset = true, bool loop = true);

  /// Stop the main animation
  void stopMainAnimation(void);

  /// Add a sub animation to this entity
  void addSubAnimation(std::string const &s,  bool reset = true, bool loop = true);

  /// Add a sub animation to this entity
  void removeSubAnimation(std::string const &s);

  /// Update all animations
  void updateAnimations(Ogre::Real);
};

#endif // !ANIMATED_ENTITY_HPP
