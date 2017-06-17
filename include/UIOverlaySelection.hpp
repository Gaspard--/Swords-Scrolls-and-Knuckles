#ifndef UI_OVERLAY_SELECTION_HPP
# define UI_OVERLAY_SELECTION_HPP

# include <memory>
# include <functional>
# include <unordered_map>
# include <Overlay/OgrePanelOverlayElement.h>
# include "Renderer.hpp"
# include "UIButton.hpp"
# include "UIOverlay.hpp"

class UIOverlaySelection : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;

  static constexpr Ogre::Real const SELECTIONBUTTON_WIDTH = 261.f / Game::WIDTH;
  static constexpr Ogre::Real const SELECTIONBUTTON_HEIGHT = 77.f / Game::HEIGHT;

public:
  UIOverlaySelection(void) = delete;
  UIOverlaySelection(Renderer &);
  UIOverlaySelection(UIOverlaySelection const &) = delete;
  UIOverlaySelection(UIOverlaySelection &&) = delete;
  UIOverlaySelection &operator=(UIOverlaySelection const &) = delete;
  UIOverlaySelection &operator=(UIOverlaySelection &&) = delete;
  virtual ~UIOverlaySelection(void) = default;
};

#endif // !UI_OVERLAY_SELECTION_HPP
