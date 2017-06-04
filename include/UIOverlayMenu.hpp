#ifndef UIOVERLAYMENU_HPP
# define UIOVERLAYMENU_HPP

# include <memory>
# include <functional>
# include <unordered_map>
# include <Overlay/OgreTextAreaOverlayElement.h>
# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreBorderPanelOverlayElement.h>
# include "UIOverlay.hpp"

class UIButton {

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

	private:
		Ogre::BorderPanelOverlayElement *button;
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
		virtual void registerCallbackByName(Ogre::String const &, std::function<void(void)>);
		virtual bool mousePressed(Ogre::Real, Ogre::Real);
		
	private:
		Ogre::Real width;
		Ogre::Real height;
		std::unordered_map<Ogre::String, std::unique_ptr<UIButton>> buttons;
		std::unordered_map<Ogre::String, std::function<void(void)>> callbacks;
		
	protected:
};

#endif // !UIOVERLAYMENU_HPP
