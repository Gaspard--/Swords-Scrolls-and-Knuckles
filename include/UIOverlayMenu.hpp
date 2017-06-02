#ifndef UIOVERLAYMENU_HPP
# define UIOVERLAYMENU_HPP

# include <Overlay/OgreTextAreaOverlayElement.h>
# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreBorderPanelOverlayElement.h>
# include <OISMouse.h>
# include "UIOverlay.hpp"

class UIButton : public OIS::MouseListener {

	public:
		UIButton(Ogre::OverlayManager *, Ogre::String const &);
		UIButton(UIButton const &) = delete;
		UIButton(UIButton &&) = delete;
		UIButton &operator=(UIButton const &) = delete;
		UIButton &operator=(UIButton &&) = delete;
		virtual ~UIButton(void) = default;
		
		void init(Ogre::OverlayManager *, Ogre::String const &, Ogre::String const &,
				Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real);
		Ogre::BorderPanelOverlayElement *getButton(void) const;
		void setCallback(std::function<void(void)>);
		
		virtual bool mouseMoved(OIS::MouseEvent const &);
		virtual bool mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID);
		virtual bool mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID);

	private:
		Ogre::BorderPanelOverlayElement *button;
		std::function<void(void)> callback;
};

class UIOverlayMenu : public UIOverlay {

	public:
		UIOverlayMenu() = default;
		UIOverlayMenu(UIOverlayMenu const &) = delete;
		UIOverlayMenu(UIOverlayMenu &&) = delete;
		UIOverlayMenu &operator=(UIOverlayMenu const &) = delete;
		UIOverlayMenu &operator=(UIOverlayMenu &&) = delete;
		virtual ~UIOverlayMenu(void) = default;
		
		virtual void init(Ogre::OverlayManager *);
		
		void registerCallbackByName(Ogre::String const &, std::function<void(void)>);

	private:
		Ogre::Real width;
		Ogre::Real height;
		std::map<Ogre::String, UIButton *> buttons;
		
	protected:
};

#endif // !UIOVERLAYMENU_HPP
