#include "UIManager.hpp"

std::map<Ogre::String, std::unique_ptr<UIOverlay>> UIManager::overlays;

UIManager::UIManager(void)
{}

void UIManager::init() {

	std::unique_ptr<UIOverlay> hud(new UIOverlayHUD());
	Ogre::Overlay *overlayHUD = Ogre::OverlayManager::getSingleton().create("hud");
	hud->setOverlay(overlayHUD);
	hud->init(Ogre::OverlayManager::getSingletonPtr());

	overlays["hud"] = std::move(hud);

	std::unique_ptr<UIOverlay> menu(new UIOverlayMenu());
	Ogre::Overlay *overlayMenu = Ogre::OverlayManager::getSingleton().create("menu");
	menu->setOverlay(overlayMenu);
	menu->init(Ogre::OverlayManager::getSingletonPtr());

	overlays["menu"] = std::move(menu);
}

// PUBLIC FUNCTIONS

void UIManager::showOverlayByName(std::string const &name) {

	overlays[name]->getOverlay()->show();
}

void UIManager::hideOverlayByName(std::string const &name) {

	overlays[name]->getOverlay()->hide();
}

void UIManager::hideAllOverlays(void) {

	for (auto &&overlay : overlays) {
		overlay.second->getOverlay()->hide();
	}
}

std::unique_ptr<UIOverlay> &UIManager::getByName(Ogre::String const &name) {

	return overlays[name];
}
