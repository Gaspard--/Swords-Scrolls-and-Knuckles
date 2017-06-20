#ifndef UI_OVERLAY_SELECTION_HPP
# define UI_OVERLAY_SELECTION_HPP

# include <memory>
# include <utility>
# include <functional>
# include <vector>
# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreTextAreaOverlayElement.h>
# include "UIOverlayResource.hpp"
# include "AnimatedEntity.hpp"
# include "Renderer.hpp"
# include "UIButton.hpp"
# include "UIOverlay.hpp"
# include "Skins.hpp"

enum class Gameplays : int {
  KEYBOARD = 0,
  JOYSTICK = 1,
  IA = 2,
  NONE = 3,
  SIZE = 4,
};


class UIOverlaySelection : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;
  size_t selected;
  std::vector<UIOverlayResource<Ogre::TextAreaOverlayElement>> gameplaysTxt;
  std::vector<Gameplays> gameplays;
  std::vector<AnimatedEntity> heroes;
  std::vector<int> skins;
  Ogre::Node *cameraNode;

  static constexpr Ogre::Real const SELECTIONBUTTON_WIDTH = 261.f / Game::WIDTH;
  static constexpr Ogre::Real const SELECTIONBUTTON_HEIGHT = 77.f / Game::HEIGHT;
  static Skins::Skin HEROES_SKINS[4][2];
  static char const *GAMEPLAYS_NAME[];

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
  void renderGameplayName(size_t);
  void changeGameplay(bool b);
};

#endif // !UI_OVERLAY_SELECTION_HPP
