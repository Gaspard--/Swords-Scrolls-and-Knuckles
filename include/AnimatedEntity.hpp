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
  constexpr AnimatedEntity(void)
    : entity()
  {}

  AnimatedEntity(Renderer &renderer,
		 std::string const &mesh);

  AnimatedEntity(Renderer &renderer,
		 std::string const &mesh,
		 Ogre::SceneNode *parent);

  constexpr AnimatedEntity(AnimatedEntity const &ae)
    : entity(ae.entity)
  {}

  constexpr AnimatedEntity(AnimatedEntity &&ae)
    : entity(ae.entity)
  {}

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
