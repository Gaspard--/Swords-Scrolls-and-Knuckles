#ifndef UIMANAGER_HPP
# define UIMANAGER_HPP

# include <Overlay/OgreOverlayManager.h>
# include "UIOverlay.hpp"
# include "UIOverlayHUD.hpp"
# include "UIOverlayMenu.hpp"

class UIManager {

	public:
		UIManager(UIManager const &) = delete;
		UIManager(UIManager &&) = delete;
		UIManager &operator=(UIManager const &) = delete;
		UIManager &operator=(UIManager &&) = delete;
		~UIManager(void) = default;
		
		static void init();
		
		static void showOverlayByName(std::string const &);
		static void hideOverlayByName(std::string const &);
		static void hideAllOverlays(void);
		static UIOverlay *getByName(Ogre::String const &);
		
		static std::vector<UIOverlay *> getOverlays(void);
		
	private:
		UIManager();
		
		static std::map<Ogre::String, UIOverlay *> overlays;
		
	protected:
};

#endif // !UIMANAGER_HPP
