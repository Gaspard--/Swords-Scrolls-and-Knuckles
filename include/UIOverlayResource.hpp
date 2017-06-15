#ifndef UI_OVERLAY_RESOURCE_HPP
# define UI_OVERLAY_RESOURCE_HPP

# include <memory>
# include <Overlay/OgreOverlaySystem.h>

template<typename T>
class UIOverlayResource
{
private:
  T *resource;

public:
  UIOverlayResource(void)
    : resource(nullptr)
  {}

  UIOverlayResource(T *r)
    : resource(r)
  {}

  UIOverlayResource(Ogre::OverlayElement *r)
    : resource(static_cast<T *>(r))
  {}

  UIOverlayResource(UIOverlayResource const &) = delete;
  UIOverlayResource(UIOverlayResource &&) = delete;
  UIOverlayResource &operator=(UIOverlayResource const &) = delete;
  UIOverlayResource &operator=(UIOverlayResource &&) = delete;
  ~UIOverlayResource() {
    Ogre::OverlayManager::getSingleton().destroyOverlayElement(resource);
  }

  T *operator->(void) {
    return (resource);
  }

  T *get(void) const {
    return (resource);
  }

  void reset(T *t) {
    if (resource != nullptr)
      Ogre::OverlayManager::getSingleton().destroyOverlayElement(resource);
    resource = t;
  }

  void reset(Ogre::OverlayElement *t) {
    if (resource != nullptr)
      Ogre::OverlayManager::getSingleton().destroyOverlayElement(resource);
    resource = static_cast<T *>(t);
  }
};

template<>
class UIOverlayResource<Ogre::Overlay>
{
private:
  Ogre::Overlay *resource;

public:
  UIOverlayResource(void)
    : resource(nullptr)
  {}

  UIOverlayResource(Ogre::Overlay *r)
    : resource(r)
  {}

  UIOverlayResource(UIOverlayResource const &) = delete;
  UIOverlayResource(UIOverlayResource &&) = delete;
  UIOverlayResource &operator=(UIOverlayResource const &) = delete;
  UIOverlayResource &operator=(UIOverlayResource &&) = delete;
  ~UIOverlayResource() {
    Ogre::OverlayManager::getSingleton().destroy(resource);
  }

  Ogre::Overlay *operator->(void) {
    return (resource);
  }

  Ogre::Overlay *get(void) const {
    return (resource);
  }

  void reset(Ogre::Overlay *&&t) {
    if (resource != nullptr)
      Ogre::OverlayManager::getSingleton().destroy(resource);
    resource = t;
  }
};

#endif // !UI_OVERLAY_RESOURCE_HPP
