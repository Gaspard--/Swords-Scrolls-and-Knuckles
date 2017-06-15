#ifndef UIOVERLAYMENU_HPP
# define UIOVERLAYMENU_HPP

# include <memory>
# include <functional>
# include <unordered_map>
# include "Renderer.hpp"
# include "UIButton.hpp"
# include "UIOverlay.hpp"

class UIOverlayMenu : public UIOverlay {
private:
  Ogre::Real width;
  Ogre::Real height;
  Ogre::PanelOverlayElement *bg;
  Ogre::TextAreaOverlayElement *title;

public:
  UIOverlayMenu(void) = delete;
  UIOverlayMenu(Renderer &);
  UIOverlayMenu(UIOverlayMenu const &) = delete;
  UIOverlayMenu(UIOverlayMenu &&) = delete;
  UIOverlayMenu &operator=(UIOverlayMenu const &) = delete;
  UIOverlayMenu &operator=(UIOverlayMenu &&) = delete;
  virtual ~UIOverlayMenu(void);

};

#endif // !UIOVERLAYMENU_HPP
