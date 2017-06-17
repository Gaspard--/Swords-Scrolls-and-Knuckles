#ifndef UIBUTTON_HPP
# define UIBUTTON_HPP

# include <Overlay/OgreOverlaySystem.h>
# include "Game.hpp"
# include "UIOverlayResource.hpp"
# include <Overlay/OgrePanelOverlayElement.h>

class UIButton
{
private:
  UIOverlayResource<Ogre::PanelOverlayElement> panel;
  UIOverlayResource<Ogre::PanelOverlayElement> hoverPanel;
  std::function<void(void)> callback;
  Ogre::Real width;
  Ogre::Real height;
  Ogre::Real offset;

public:
  static constexpr Ogre::Real const DEFAULT_WIDTH = 710.f / Game::WIDTH;
  static constexpr Ogre::Real const DEFAULT_HEIGHT = 108.f / Game::HEIGHT;
  static constexpr Ogre::Real const DEFAULT_HOVER_OFFSET = 0.012f;

  UIButton(Ogre::OverlayManager *, Ogre::String const &, std::function<void(void)> const &,
  Ogre::Real = DEFAULT_WIDTH, Ogre::Real = DEFAULT_HEIGHT, Ogre::Real = DEFAULT_HOVER_OFFSET);
  UIButton(UIButton const &) = delete;
  UIButton(UIButton &&) = delete;
  UIButton &operator=(UIButton const &) = delete;
  UIButton &operator=(UIButton &&) = delete;
  ~UIButton(void) = default;

  void init(
    Ogre::String const &,
    Ogre::Real,
    Ogre::Real
  );

  Ogre::PanelOverlayElement *getPanel(void) const;
  std::function<void(void)> const &getCallback(void) const;
  void setHovered(bool);
};

#endif // !UIBUTTON_HPP
