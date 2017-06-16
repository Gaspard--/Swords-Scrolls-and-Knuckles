#ifndef UIOVERLAY_HPP
# define UIOVERLAY_HPP

# include <unordered_map>
# include <memory>
# include "Joystick.hpp"
# include "UIButton.hpp"

class UIOverlay {
private:

protected:
  UIOverlayResource<Ogre::Overlay> overlay;
  std::vector<std::unique_ptr<UIButton>> buttons;
  size_t selectedButton;

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

  void mousePressed(Ogre::Real, Ogre::Real);
  void mouseMoved(Ogre::Real, Ogre::Real);

  virtual void resetUICallbacks(void);
  bool isVisible(void) const;
  virtual void setUIVisible(bool);

  void setSelectedButton(int i);
  size_t getSelectedButton(void) const;
};

#endif // !UIOVERLAY_HPP
