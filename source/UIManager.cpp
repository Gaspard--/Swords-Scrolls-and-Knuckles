#include "UIManager.hpp"

UIManager::UIManager()
	: overlayManager(Ogre::OverlayManager::getSingletonPtr())
{
	
	UIOverlayHUD *hud = new UIOverlayHUD();
	Ogre::Overlay *overlayHUD = overlayManager->create("hud");
	hud->setOverlay(overlayHUD);
	hud->init(overlayManager);

	UIOverlayMenu *menu = new UIOverlayMenu();
	Ogre::Overlay *overlayMenu = overlayManager->create("menu");
	menu->setOverlay(overlayMenu);
	menu->init(overlayManager);
}

// PUBLIC FUNCTIONS

void UIManager::showOverlayByName(std::string const &name) {

	overlayManager->getByName(name)->show();
}

void UIManager::hideOverlayByName(std::string const &name) {

	overlayManager->getByName(name)->hide();
}

void UIManager::hideAllOverlays(void) {

	Ogre::OverlayManager::OverlayMapIterator it = overlayManager->getOverlayIterator();
	while (it.hasMoreElements()) {
		auto pair = it.getNext();
		pair->hide();
	}
}
