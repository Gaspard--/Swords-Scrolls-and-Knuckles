#include "UIManager.hpp"

std::map<Ogre::String, UIOverlay *> UIManager::overlays;

UIManager::UIManager(void)
{}

void UIManager::init() {

	UIOverlayHUD *hud = new UIOverlayHUD();
	Ogre::Overlay *overlayHUD = Ogre::OverlayManager::getSingleton().create("hud");
	hud->setOverlay(overlayHUD);
	hud->init(Ogre::OverlayManager::getSingletonPtr());
	
	overlays["hud"] = hud;

	UIOverlayMenu *menu = new UIOverlayMenu();
	Ogre::Overlay *overlayMenu = Ogre::OverlayManager::getSingleton().create("menu");
	menu->setOverlay(overlayMenu);
	menu->init(Ogre::OverlayManager::getSingletonPtr());
	
	overlays["menu"] = menu;
}

// PUBLIC FUNCTIONS

std::vector<UIOverlay *> UIManager::getOverlays(void) {

	std::vector<UIOverlay *> ov;
	
	std::map<Ogre::String, UIOverlay *>::iterator it;
	for (it = overlays.begin(); it != overlays.end(); ++it) {
		ov.push_back(it->second);
	}
	
	return ov;
}

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
