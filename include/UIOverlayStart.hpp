#ifndef UIOVERLAYSTART_HPP
# define UIOVERLAYSTART_HPP

# include <ctime>
# include <chrono>
# include <Overlay/OgreTextAreaOverlayElement.h>
# include "Game.hpp"
# include "UIOverlay.hpp"

class UIOverlayStart : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;
	UIOverlayResource<Ogre::TextAreaOverlayElement> pressTxt;
	std::chrono::time_point<std::chrono::system_clock> startTime;
	
	void initText(UIOverlayResource<Ogre::TextAreaOverlayElement> &,
					Ogre::DisplayString const &, Ogre::Real, Ogre::Real, Ogre::ColourValue);
	void updateText(void);
	void switchBG(void);

public:
  static constexpr Ogre::Real const LOGO_WIDTH = 390.f / Game::WIDTH;
  static constexpr Ogre::Real const LOGO_HEIGHT = 500.f / Game::HEIGHT;
	
  UIOverlayStart(void) = delete;
  UIOverlayStart(Renderer &);
  UIOverlayStart(UIOverlayStart const &) = delete;
  UIOverlayStart(UIOverlayStart &&) = delete;
  UIOverlayStart &operator=(UIOverlayStart const &) = delete;
  UIOverlayStart &operator=(UIOverlayStart &&) = delete;
  virtual ~UIOverlayStart(void) = default;
	
	void update(void);
};

#endif // !UIOVERLAYSTART_HPP
