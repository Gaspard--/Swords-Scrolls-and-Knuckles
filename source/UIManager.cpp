#include "UIManager.hpp"

UIManager::UIManager()
	: overlayManager(Ogre::OverlayManager::getSingletonPtr())
{
	
	UIOverlayHUD *hud = new UIOverlayHUD();
	Ogre::Overlay *overlayHUD = overlayManager->create("hud");
	hud->setOverlay(overlayHUD);
	hud->init(overlayManager);
	
	overlays["hud"] = hud;

	UIOverlayMenu *menu = new UIOverlayMenu();
	Ogre::Overlay *overlayMenu = overlayManager->create("menu");
	menu->setOverlay(overlayMenu);
	menu->init(overlayManager);
	
	overlays["menu"] = menu;
}

// PUBLIC FUNCTIONS

void UIManager::showOverlayByName(std::string const &name) {

	overlays[name]->getOverlay()->show();
}

void UIManager::hideOverlayByName(std::string const &name) {

	overlays[name]->getOverlay()->hide();
}

void UIManager::hideAllOverlays(void) {

	std::map<Ogre::String, UIOverlay *>::iterator it;
	for (it = overlays.begin(); it != overlays.end(); ++it) {
		it->second->getOverlay()->hide();
	}
}

UIOverlay *UIManager::getByName(Ogre::String const &name) {

	return overlays[name];
}
