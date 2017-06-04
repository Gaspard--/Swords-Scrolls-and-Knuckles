#ifndef UIMANAGER_HPP
# define UIMANAGER_HPP

# include <memory>
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
		static std::unique_ptr<UIOverlay> &getByName(Ogre::String const &);
		
	private:
		UIManager();
		static std::map<Ogre::String, std::unique_ptr<UIOverlay>> overlays;
		
	protected:
};

#endif // !UIMANAGER_HPP
