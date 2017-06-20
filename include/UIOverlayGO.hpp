#ifndef UIOVERLAYGO_HPP
# define UIOVERLAYGO_HPP

# include "UIOverlay.hpp"
# include "SceneMainMenu.hpp"
# include "SceneSelection.hpp"
# include "SceneScoreboard.hpp"

class UIOverlayGO : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;
	
public:
  static constexpr Ogre::Real const BUTTON_WIDTH = 391.f / Game::WIDTH;
  static constexpr Ogre::Real const BUTTON_HEIGHT = 115.f / Game::HEIGHT;
	
  UIOverlayGO(void) = delete;
  UIOverlayGO(Renderer &);
  UIOverlayGO(UIOverlayGO const &) = delete;
  UIOverlayGO(UIOverlayGO &&) = delete;
  UIOverlayGO &operator=(UIOverlayGO const &) = delete;
  UIOverlayGO &operator=(UIOverlayGO &&) = delete;
  virtual ~UIOverlayGO(void) = default;
};
#endif // !UIOVERLAYGO_HPP
