#ifndef UI_OVERLAY_SELECTION_HPP
# define UI_OVERLAY_SELECTION_HPP

# include <memory>
# include <functional>
# include <vector>
# include <Overlay/OgrePanelOverlayElement.h>
# include "AnimatedEntity.hpp"
# include "Renderer.hpp"
# include "UIButton.hpp"
# include "UIOverlay.hpp"

class UIOverlaySelection : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;
  std::vector<AnimatedEntity> heroes;
  Ogre::Node *cameraNode;
  Entity wall;

  static constexpr Ogre::Real const SELECTIONBUTTON_WIDTH = 261.f / Game::WIDTH;
  static constexpr Ogre::Real const SELECTIONBUTTON_HEIGHT = 77.f / Game::HEIGHT;

  void setHeroDefault(AnimatedEntity &ae, size_t);

public:
  UIOverlaySelection(void) = delete;
  UIOverlaySelection(Renderer &);
  UIOverlaySelection(UIOverlaySelection const &) = delete;
  UIOverlaySelection(UIOverlaySelection &&) = delete;
  UIOverlaySelection &operator=(UIOverlaySelection const &) = delete;
  UIOverlaySelection &operator=(UIOverlaySelection &&) = delete;
  virtual ~UIOverlaySelection(void) = default;

  void updateUI(Ogre::Real x);
  void changeSkin(size_t i, bool);
};

#endif // !UI_OVERLAY_SELECTION_HPP
