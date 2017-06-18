#ifndef UI_OVERLAY_SELECTION_HPP
# define UI_OVERLAY_SELECTION_HPP

# include <memory>
# include <utility>
# include <functional>
# include <vector>
# include <Overlay/OgrePanelOverlayElement.h>
# include "AnimatedEntity.hpp"
# include "Renderer.hpp"
# include "UIButton.hpp"
# include "UIOverlay.hpp"
# include "Skins.hpp"

class UIOverlaySelection : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;
  size_t selected;
  std::vector<AnimatedEntity> heroes;
  std::vector<int> skins;
  Ogre::Node *cameraNode;

  static constexpr Ogre::Real const SELECTIONBUTTON_WIDTH = 261.f / Game::WIDTH;
  static constexpr Ogre::Real const SELECTIONBUTTON_HEIGHT = 77.f / Game::HEIGHT;
  static Skins::Skin HEROES_SKINS[4][2];

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
  void changeSkin(Renderer &, bool);
  void changeSelection(bool);
};

#endif // !UI_OVERLAY_SELECTION_HPP
