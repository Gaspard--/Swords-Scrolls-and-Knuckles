#ifndef UI_OVERLAY_PAUSE_HPP
# define UI_OVERLAY_PAUSE_HPP

# include <memory>
# include <functional>
# include <unordered_map>
# include "Renderer.hpp"
# include "UIButton.hpp"
# include "UIOverlay.hpp"

class UIOverlayPause : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;

public:
  UIOverlayPause(void) = delete;
  UIOverlayPause(Renderer &);
  UIOverlayPause(UIOverlayPause const &) = delete;
  UIOverlayPause(UIOverlayPause &&) = delete;
  UIOverlayPause &operator=(UIOverlayPause const &) = delete;
  UIOverlayPause &operator=(UIOverlayPause &&) = delete;
  virtual ~UIOverlayPause(void) = default;
};

#endif // !UI_OVERLAY_PAUSE_HPP
