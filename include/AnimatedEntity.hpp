#ifndef ANIMATED_ENTITY_HPP
# define ANIMATED_ENTITY_HPP

# include <map>
# include <vector>
# include <string>
# include <OgreAnimationState.h>
# include "Entity.hpp"

class AnimatedEntity
{
  Entity entity;

public:

  template<class... P>
  AnimatedEntity(P&&... params)
    : entity(std::forward<P>(params)...)
  {}

  constexpr AnimatedEntity(AnimatedEntity const &ae) = default;
  constexpr AnimatedEntity(AnimatedEntity &&ae) = default;

  AnimatedEntity &operator=(AnimatedEntity const &) = default;
  AnimatedEntity &operator=(AnimatedEntity &&) = default;
  ~AnimatedEntity(void) = default;

  /// Return the entity
  Entity &getEntity(void);
  Entity const &getEntity(void) const;

  /// Stop all animations
  void stopAnimation(void);

  /// Set the animation for this entity
  void setAnimation(std::string const &s, bool reset = true, bool loop = true);

  /// Add an animation to this entity
  void addAnimation(std::string const &s,  bool reset = true, bool loop = true);

  /// Remove an animation to this entity
  void removeAnimation(std::string const &s);

  /// Update all animations
  void updateAnimations(Ogre::Real);
};

#endif // !ANIMATED_ENTITY_HPP
