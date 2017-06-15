#ifndef UIBUTTON_HPP
# define UIBUTTON_HPP

# include <Overlay/OgreOverlaySystem.h>
# include "Game.hpp"

class UIButton
{
private:
  Ogre::PanelOverlayElement *panel;
  Ogre::PanelOverlayElement *hoverPanel;
  std::function<void(void)> callback;

public:
  static constexpr Ogre::Real const WIDTH = 710.f / Game::WIDTH;
  static constexpr Ogre::Real const HEIGHT = 108.f / Game::HEIGHT;

  UIButton(Ogre::OverlayManager *, Ogre::String const &, std::function<void(void)> const &);
  UIButton(UIButton const &) = delete;
  UIButton(UIButton &&) = delete;
  UIButton &operator=(UIButton const &) = delete;
  UIButton &operator=(UIButton &&) = delete;
  ~UIButton(void);

  void init(
    Ogre::OverlayManager *,
    Ogre::String const &,
    Ogre::Real,
    Ogre::Real
  );

  Ogre::PanelOverlayElement *getPanel(void) const;
  std::function<void(void)> const &getCallback(void) const;
  void setHovered(bool);
};

#endif // !UIBUTTON_HPP
