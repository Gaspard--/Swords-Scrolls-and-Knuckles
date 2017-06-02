#include "UIOverlayHUD.hpp"

// UICharStat

UICharStat::UICharStat(Ogre::OverlayManager *manager, Ogre::String const &name) {

	panel
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", name));
}

void UICharStat::init(Ogre::String const &materialName, Ogre::String const &borderName,
		Ogre::Real width, Ogre::Real height, Ogre::Real x, Ogre::Real y) {
	
	panel->setMaterialName(materialName);
	panel->setDimensions(0.25 * width, height);
	panel->setPosition(x, y);
	
	panel->setBorderMaterialName(borderName);
	panel->setBorderSize(0.0075);
}

void UICharStat::initText(Ogre::OverlayManager *manager, Ogre::String const &elementName,
		Ogre::DisplayString const &txt) {

	Ogre::Vector2 panelSize = UIOverlay::relativeToPixels({panel->getWidth(), panel->getHeight()});
	Ogre::Vector2 panelPos = UIOverlay::relativeToPixels({panel->getLeft(), panel->getTop()});
	
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
	scoreTxt->setTop(panelPos.y + panelSize.y / 5.0 * 3.0);
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
	
	panel->addChild(text);
	panel->addChild(scoreTxt);
	panel->addChild(healthTxt);
}

void UICharStat::updateScore(Ogre::String const &name, int score) {

	std::string data(name);
	data += "TextScore";
	Ogre::TextAreaOverlayElement *scoreTxt
		= static_cast<Ogre::TextAreaOverlayElement *>(panel->getChild(data));
	scoreTxt->setCaption("Score: " + std::to_string(score));
}

void UICharStat::updateHealth(Ogre::String const &name, int health) {

	std::string data(name);
	data += "TextHealth";
	Ogre::TextAreaOverlayElement *healthTxt
		= static_cast<Ogre::TextAreaOverlayElement *>(panel->getChild(data));
	healthTxt->setCaption("Health: " + std::to_string(health));
}

Ogre::BorderPanelOverlayElement *UICharStat::getPanel(void) const {

	return panel;
}

// UIOverlayHUD

UIOverlayHUD::~UIOverlayHUD(void) {

	delete chars["Wizzard"];
	delete chars["Warrior"];
	delete chars["Archer"];
	delete chars["Valkyrie"];
}

void UIOverlayHUD::init(Ogre::OverlayManager *manager) {

	std::clog << "Overlay HUD init." << std::endl;
	width = 0.5;
	height = 0.15;

	Ogre::PanelOverlayElement *stats
		= static_cast<Ogre::PanelOverlayElement *>(manager->createOverlayElement("Panel", "Stats"));
	stats->setDimensions(width, height);
	stats->setPosition(0.5 - width / 2, 1 - height);

	UICharStat *wizzard = new UICharStat(manager, "Wizzard");
	wizzard->init("HUD/Black", "HUD/Yellow", width, height, 0.0, 0.0);
	wizzard->initText(manager, "WizzardText", "Wizzard");
	chars["Wizzard"] = wizzard;
	
	UICharStat *warrior = new UICharStat(manager, "Warrior");
	warrior->init("HUD/Black", "HUD/Red", width, height, 0.25 * width, 0.0);
	warrior->initText(manager, "WarriorText", "Warrior");
	chars["Warrior"] = warrior;
	
	UICharStat *archer = new UICharStat(manager, "Archer");
	archer->init("HUD/Black", "HUD/Green", width, height, 0.25 * width * 2.0, 0.0);
	archer->initText(manager, "ArcherText", "Archer");
	chars["Archer"] = archer;
	
	UICharStat *valkyrie = new UICharStat(manager, "Valkyrie");
	valkyrie->init("HUD/Black", "HUD/Blue", width, height, 0.25 * width * 3.0, 0.0);
	valkyrie->initText(manager, "ValkyrieText", "Valkyrie");
	
	stats->addChild(wizzard->getPanel());
	stats->addChild(warrior->getPanel());
	stats->addChild(archer->getPanel());
	stats->addChild(valkyrie->getPanel());
	overlay->add2D(stats);
}

void UIOverlayHUD::updateScoreByName(Ogre::String const &name, int score) {

	chars[name]->updateScore(name, score);
}

void UIOverlayHUD::updateHealthByName(Ogre::String const &name, int health) {

	chars[name]->updateHealth(name, health);
}
