#ifndef UIMANAGER_HPP
# define UIMANAGER_HPP

# include <Overlay/OgreOverlayManager.h>
# include "UIOverlay.hpp"
# include "UIOverlayHUD.hpp"
# include "UIOverlayMenu.hpp"

class UIManager : public Ogre::OverlayManager {

	public:
		UIManager();
		UIManager(UIManager const &) = delete;
		UIManager(UIManager &&) = delete;
		UIManager &operator=(UIManager const &) = delete;
		UIManager &operator=(UIManager &&) = delete;
		~UIManager(void);
		
		void showOverlayByName(std::string const &);
		void hideOverlayByName(std::string const &);
		void hideAllOverlays(void);
		
	private:
		
	protected:
};

#endif // !UIMANAGER_HPP
