#ifndef UIOVERLAY_HPP
# define UIOVERLAY_HPP

# include <unordered_map>
# include <memory>
# include "UIButton.hpp"

class UIOverlay {
private:

protected:
  UIOverlayResource<Ogre::Overlay> overlay;
  std::unordered_map<Ogre::String, std::unique_ptr<UIButton>> buttons;

public:
  UIOverlay() = delete;
  UIOverlay(std::string const &);
  UIOverlay(UIOverlay const &) = delete;
  UIOverlay(UIOverlay &&) = delete;
  UIOverlay &operator=(UIOverlay const &) = delete;
  UIOverlay &operator=(UIOverlay &&) = delete;
  virtual ~UIOverlay(void) = default;

  static Ogre::Vector2 pixelsToRelative(Ogre::Vector2);
  static Ogre::Vector2 relativeToPixels(Ogre::Vector2);

  Ogre::Overlay *getOverlay(void) const;

  bool mousePressed(Ogre::Real, Ogre::Real);
};

#endif // !UIOVERLAY_HPP
