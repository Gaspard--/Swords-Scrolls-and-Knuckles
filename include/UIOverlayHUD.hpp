#ifndef UIOVERLAYHUD_HPP
# define UIOVERLAYHUD_HPP

# include <Overlay/OgreTextAreaOverlayElement.h>
# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreBorderPanelOverlayElement.h>
# include "UIOverlay.hpp"
# include "UIChar.hpp"

class UICharStat {

	public:
		UICharStat(Ogre::OverlayManager *, Ogre::String const &);
		UICharStat(UICharStat const &) = delete;
		UICharStat(UICharStat &&) = delete;
		UICharStat &operator=(UICharStat const &) = delete;
		UICharStat &operator=(UICharStat &&) = delete;
		virtual ~UICharStat(void) = default;
		
		void init(Ogre::String const &, Ogre::String const &,
				Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real);
		void initText(Ogre::OverlayManager *, Ogre::String const &, Ogre::DisplayString const &);
		
		void updateScore(Ogre::String const &, int);
		void updateHealth(Ogre::String const &, int);
		
		Ogre::BorderPanelOverlayElement *getPanel(void) const;
		
	private:
		Ogre::BorderPanelOverlayElement *panel;
		UIChar *character;
};

class UIOverlayHUD : public UIOverlay {

	public:
		UIOverlayHUD() = default;
		UIOverlayHUD(UIOverlayHUD const &) = delete;
		UIOverlayHUD(UIOverlayHUD &&) = delete;
		UIOverlayHUD &operator=(UIOverlayHUD const &) = delete;
		UIOverlayHUD &operator=(UIOverlayHUD &&) = delete;
		virtual ~UIOverlayHUD(void);

		virtual void init(Ogre::OverlayManager *);
		
		void updateScoreByName(Ogre::String const &, int);
		void updateHealthByName(Ogre::String const &, int);

	private:
		Ogre::Real width;
		Ogre::Real height;
		std::map<Ogre::String, UICharStat *> chars;
};

#endif // !UIOVERLAYHUD_HPP
