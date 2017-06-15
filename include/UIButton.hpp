#ifndef UIBUTTON_HPP
# define UIBUTTON_HPP

# include <Overlay/OgreOverlaySystem.h>

class UIButton
{
private:
  Ogre::BorderPanelOverlayElement *panel;
  Ogre::TextAreaOverlayElement *text;
  std::function<void(void)> callback;

public:
  UIButton(Ogre::OverlayManager *, Ogre::String const &, std::function<void(void)> const &);
  UIButton(UIButton const &) = delete;
  UIButton(UIButton &&) = delete;
  UIButton &operator=(UIButton const &) = delete;
  UIButton &operator=(UIButton &&) = delete;
  ~UIButton(void);

  void init(
    Ogre::OverlayManager *,
    Ogre::String const &,
    Ogre::String const &,
    Ogre::Real,
    Ogre::Real,
    Ogre::Real,
    Ogre::Real
  );

  Ogre::BorderPanelOverlayElement *getPanel(void) const;
  std::function<void(void)> const &getCallback(void) const;
};

#endif // !UIBUTTON_HPP
