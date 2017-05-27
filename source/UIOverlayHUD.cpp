#include "UIOverlayHUD.hpp"

void UIOverlayHUD::init(Ogre::OverlayManager *manager) {

	std::clog << "Overlay HUD init." << std::endl;
	
	Ogre::PanelOverlayElement *stats
		= static_cast<Ogre::PanelOverlayElement *>(manager->createOverlayElement("Panel", "Stats"));
	stats->setMaterialName("HUD/White");
	stats->setDimensions(0.5, 0.15);
	stats->setPosition(0.25, 0.85);
	
	Ogre::BorderPanelOverlayElement *wizzard
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", "Wizzard"));
	wizzard->setMaterialName("HUD/Yellow");
	wizzard->setDimensions(0.25 * 0.5, 1);
	wizzard->setPosition(0, 0);
	
	Ogre::BorderPanelOverlayElement *warrior
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", "Warrior"));
	warrior->setMaterialName("HUD/Red");
	warrior->setDimensions(0.25 * 0.5, 1);
	warrior->setPosition(0.25 * 0.5, 0);

	Ogre::BorderPanelOverlayElement *bowman
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", "Bowman"));
	bowman->setMaterialName("HUD/Green");
	bowman->setDimensions(0.25 * 0.5, 1);
	bowman->setPosition(0.25 * 0.5 * 2, 0);

	Ogre::BorderPanelOverlayElement *valkyrie
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", "Valkyrie"));
	valkyrie->setMaterialName("HUD/Blue");
	valkyrie->setDimensions(0.25 * 0.5, 1);
	valkyrie->setPosition(0.25 * 0.5 * 3, 0);
	
	stats->addChild(wizzard);
	stats->addChild(warrior);
	stats->addChild(bowman);
	stats->addChild(valkyrie);
	overlay->add2D(stats);
}
