#ifndef ANIMATED_ENTITY_HPP
# define ANIMATED_ENTITY_HPP

# include <map>
# include <memory>
# include <vector>
# include <string>
# include <OgreAnimationState.h>
# include "Entity.hpp"
# include "Animations.hpp"

class AnimatedEntity
{
  Entity entity;
  Ogre::AnimationState *mainAnimation;
  Ogre::AnimationState *targetMainAnimation;
  Ogre::Real blendDuration;
  Ogre::Real blendTimer;
  std::unique_ptr<AnimatedEntity> entityMount;

public:

  template<class... P>
  AnimatedEntity(P&&... params)
    : entity(std::forward<P>(params)...)
    , mainAnimation(entity.getOgre()->getAnimationState(Animations::IDLE))
    , targetMainAnimation(nullptr)
    , blendDuration(0.f)
    , blendTimer(0.f)
    , entityMount(nullptr)
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
  void setMainAnimation(std::string const &s, Ogre::Real blender_duration = 0.1f);

  /// Add a sub animation to this entity
  void addSubAnimation(std::string const &s,  bool reset = true, bool loop = false);

  /// Update all animations
  void updateAnimations(Ogre::Real);

  /// Add an entity as a mount.
  /// Takes the ownership of the given pointer
  void setMount(AnimatedEntity *mount);

  /// Activate the mount.
  void mount(void);

  /// Disactiate the mount.
  void dismount(void);

  /// Returns a pointer to the mount, or nullptr if there is no mount for this AnimatedEntity.
  AnimatedEntity *getMount(void);

  /// Is this entity on a mount ?
  bool isMounted(void);
};

#endif // !ANIMATED_ENTITY_HPP
