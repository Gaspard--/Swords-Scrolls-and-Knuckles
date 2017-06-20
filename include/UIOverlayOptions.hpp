#ifndef UIOVERLAY_OPTIONS_HPP
# define UIOVERLAY_OPTIONS_HPP

# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreTextAreaOverlayElement.h>
# include "UIOverlayResource.hpp"
# include "UIOverlay.hpp"

class UIOverlayOptions : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;
  std::vector<UIOverlayResource<Ogre::TextAreaOverlayElement>> optionsTxt;

public:
  static constexpr Ogre::Real const OPTIONSBUTTON_WIDTH = 261.f / Game::WIDTH;
  static constexpr Ogre::Real const OPTIONSBUTTON_HEIGHT = 77.f / Game::HEIGHT;

  UIOverlayOptions(void) = delete;
  UIOverlayOptions(Renderer &);
  UIOverlayOptions(UIOverlayOptions const &) = delete;
  UIOverlayOptions(UIOverlayOptions &&) = delete;
  UIOverlayOptions &operator=(UIOverlayOptions const &) = delete;
  UIOverlayOptions &operator=(UIOverlayOptions &&) = delete;
  virtual ~UIOverlayOptions(void) = default;

  void updateSelectedOptions(Renderer &);
};

#endif // !UIOVERLAY_OPTIONS_HPP
