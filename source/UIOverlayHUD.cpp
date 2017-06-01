#include "UIOverlayHUD.hpp"

// UICharStat

UICharStat::UICharStat(Ogre::String const &name)
	: Ogre::BorderPanelOverlayElement(name)
{
}

void UICharStat::init(Ogre::String const &materialName, Ogre::String const &borderName,
		Ogre::Real width, Ogre::Real height, Ogre::Real x, Ogre::Real y) {
	
	setMaterialName(materialName);
	setDimensions(0.25 * width, height);
	setPosition(x, y);
	
	setBorderMaterialName(borderName);
	setBorderSize(0.0075);
}

void UICharStat::initText(Ogre::OverlayManager *manager, Ogre::String const &elementName,
		Ogre::DisplayString const &txt) {

	Ogre::Vector2 panelSize = UIOverlay::relativeToPixels({getWidth(), getHeight()});
	Ogre::Vector2 panelPos = UIOverlay::relativeToPixels({getLeft(), getTop()});
	
	Ogre::TextAreaOverlayElement *text
		= static_cast<Ogre::TextAreaOverlayElement *>(manager->createOverlayElement("TextArea", elementName));
	text->setFontName("HUD/Font");
	text->setCaption(txt);
	text->setColour(Ogre::ColourValue::White);
	text->setMetricsMode(Ogre::GMM_PIXELS);
	text->setLeft(panelSize.x / 2.0);
	text->setTop(panelPos.y + panelSize.y / 5.0);
	text->setCharHeight(20);
	text->setAlignment(Ogre::TextAreaOverlayElement::Center);
	
	Ogre::TextAreaOverlayElement *scoreTxt
		= static_cast<Ogre::TextAreaOverlayElement *>(manager->createOverlayElement("TextArea", elementName + "Score"));
	scoreTxt->setFontName("HUD/Font");
	// scoreTxt->setCaption("Score: " + std::to_string(character->getScore()));
	scoreTxt->setCaption("Score");
	scoreTxt->setColour(Ogre::ColourValue::White);
	scoreTxt->setMetricsMode(Ogre::GMM_PIXELS);
	scoreTxt->setLeft(panelSize.x / 2.0);
	scoreTxt->setTop(panelPos.y + panelSize.y / 5.0 * 2.0);
	scoreTxt->setCharHeight(20);
	scoreTxt->setAlignment(Ogre::TextAreaOverlayElement::Center);

	Ogre::TextAreaOverlayElement *healthTxt
		= static_cast<Ogre::TextAreaOverlayElement *>(manager->createOverlayElement("TextArea", elementName + "Health"));
	healthTxt->setFontName("HUD/Font");
	// healthTxt->setCaption("Health: " + std::to_string(character->getHealth()));
	healthTxt->setCaption("Health");
	healthTxt->setColour(Ogre::ColourValue::White);
	healthTxt->setMetricsMode(Ogre::GMM_PIXELS);
	healthTxt->setLeft(panelSize.x / 2.0);
	healthTxt->setTop(panelPos.y + panelSize.y / 5.0 * 4.0);
	healthTxt->setCharHeight(20);
	healthTxt->setAlignment(Ogre::TextAreaOverlayElement::Center);
	
	addChild(text);
	addChild(scoreTxt);
	addChild(healthTxt);
}

// UIOverlayHUD

void UIOverlayHUD::init(Ogre::OverlayManager *manager) {

	std::clog << "Overlay HUD init." << std::endl;
	width = 0.5;
	height = 0.15;

	Ogre::PanelOverlayElement *stats
		= static_cast<Ogre::PanelOverlayElement *>(manager->createOverlayElement("Panel", "Stats"));
	stats->setMaterialName("HUD/White");
	stats->setTransparent(true);
	stats->setDimensions(width, height);
	stats->setPosition(0.5 - width / 2, 1 - height);

	Ogre::BorderPanelOverlayElement *wizzard
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", "Wizzard"));
	(static_cast<UICharStat *>(wizzard))->init("HUD/Black", "HUD/Yellow",
			width, height, 0.0, 0.0);
	(static_cast<UICharStat *>(wizzard))->initText(manager, "WizzardText", "Wizzard");
	
	Ogre::BorderPanelOverlayElement *warrior
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", "Warrior"));
	(static_cast<UICharStat *>(warrior))->init("HUD/Black", "HUD/Red",
			width, height, 0.25 * width, 0.0);
	(static_cast<UICharStat *>(warrior))->initText(manager, "WarriorText", "Warrior");
	
	Ogre::BorderPanelOverlayElement *archer
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", "Bowman"));
	(static_cast<UICharStat *>(archer))->init("HUD/Black", "HUD/Green",
			width, height, 0.25 * width * 2.0, 0.0);
	(static_cast<UICharStat *>(archer))->initText(manager, "ArcherText", "Archer");

	Ogre::BorderPanelOverlayElement *valkyrie
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", "Valkyrie"));
	(static_cast<UICharStat *>(valkyrie))->init("HUD/Black", "HUD/Blue",
			width, height, 0.25 * width * 3.0, 0.0);
	(static_cast<UICharStat *>(valkyrie))->initText(manager, "ValkyrieText", "Valkyrie");

	stats->addChild(wizzard);
	stats->addChild(warrior);
	stats->addChild(archer);
	stats->addChild(valkyrie);
	overlay->add2D(stats);
}
