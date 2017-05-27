#include "UIManager.hpp"

UIManager::UIManager()
	: Ogre::OverlayManager()
{
	// UIOverlayHUD *hud = static_cast<UIOverlayHUD *>(create("hud"));
	// UIOverlayMenu *menu = static_cast<UIOverlayMenu *>(create("menu"));
	
	UIOverlayHUD *hud = new UIOverlayHUD();
	Ogre::Overlay *overlayHUD = create("hud");
	hud->setOverlay(overlayHUD);
	hud->init();
	
	// hud->init();
	// menu->init();
}

UIManager::~UIManager(void) {

}

// PUBLIC FUNCTIONS

void UIManager::showOverlayByName(std::string const &name) {

	getByName(name)->show();
}

void UIManager::hideOverlayByName(std::string const &name) {

	getByName(name)->hide();
}

void UIManager::hideAllOverlays(void) {

	OverlayMapIterator it = getOverlayIterator();
	while (it.hasMoreElements()) {
		auto pair = it.getNext();
		pair->hide();
	}
}
