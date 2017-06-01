#ifndef UIOVERLAYHUD_HPP
# define UIOVERLAYHUD_HPP

# include <Overlay/OgreTextAreaOverlayElement.h>
# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreBorderPanelOverlayElement.h>
# include "UIOverlay.hpp"
# include "UIChar.hpp"

class UICharStat : public Ogre::BorderPanelOverlayElement {

	public:
		UICharStat(Ogre::String const &);
		UICharStat(UICharStat const &) = delete;
		UICharStat(UICharStat &&) = delete;
		UICharStat &operator=(UICharStat const &) = delete;
		UICharStat &operator=(UICharStat &&) = delete;
		virtual ~UICharStat(void) = default;
		
		void init(Ogre::String const &, Ogre::String const &,
				Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real);
		void initText(Ogre::OverlayManager *, Ogre::String const &, Ogre::DisplayString const &);
		
	private:
		UIChar *character;
};

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
		Ogre::Real width;
		Ogre::Real height;
		
	protected:
};

#endif // !UIOVERLAYHUD_HPP
