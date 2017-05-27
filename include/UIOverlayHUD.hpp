#ifndef UIOVERLAYHUD_HPP
# define UIOVERLAYHUD_HPP

# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreBorderPanelOverlayElement.h>
# include "UIOverlay.hpp"

class UIOverlayHUD : public UIOverlay {

	public:
		UIOverlayHUD() = default;
		UIOverlayHUD(UIOverlayHUD const &) = delete;
		UIOverlayHUD(UIOverlayHUD &&) = delete;
		UIOverlayHUD &operator=(UIOverlayHUD const &) = delete;
		UIOverlayHUD &operator=(UIOverlayHUD &&) = delete;
		virtual ~UIOverlayHUD(void) = default;

		virtual void init(Ogre::OverlayManager *);

	private:
	protected:
};

#endif // !UIOVERLAYHUD_HPP
