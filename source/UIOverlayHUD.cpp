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
	setText(text, txt, panelSize, panelPos, 1.0);

	Ogre::TextAreaOverlayElement *scoreTxt
		= static_cast<Ogre::TextAreaOverlayElement *>(manager->createOverlayElement("TextArea", elementName + "Score"));
	setText(scoreTxt, "Score", panelSize, panelPos, 3.0);

	Ogre::TextAreaOverlayElement *healthTxt
		= static_cast<Ogre::TextAreaOverlayElement *>(manager->createOverlayElement("TextArea", elementName + "Health"));
	setText(healthTxt, "Health", panelSize, panelPos, 4.0);
}

void UICharStat::setText(Ogre::TextAreaOverlayElement *textArea, Ogre::DisplayString const &str,
		Ogre::Vector2 panelSize, Ogre::Vector2 panelPos, Ogre::Real offsetTop) {

	textArea->setFontName("HUD/Font");
	textArea->setCaption(str);
	textArea->setColour(Ogre::ColourValue::White);
	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setLeft(panelSize.x / 2.0);
	textArea->setTop(panelPos.y + panelSize.y / 5.0 * offsetTop);
	textArea->setCharHeight(20);
	textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);

	panel->addChild(textArea);
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

void UIOverlayHUD::init(Ogre::OverlayManager *manager) {

	std::clog << "Overlay HUD init." << std::endl;
	width = 0.5;
	height = 0.15;

	Ogre::PanelOverlayElement *stats
		= static_cast<Ogre::PanelOverlayElement *>(manager->createOverlayElement("Panel", "Stats"));
	stats->setDimensions(width, height);
	stats->setPosition(0.5 - width / 2, 1 - height);

	std::unique_ptr<UICharStat> wizzard(new UICharStat(manager, "Wizzard"));
	wizzard->init("HUD/Black", "HUD/Yellow", width, height, 0.0, 0.0);
	wizzard->initText(manager, "WizzardText", "Wizzard");

	std::unique_ptr<UICharStat> warrior(new UICharStat(manager, "Warrior"));
	warrior->init("HUD/Black", "HUD/Red", width, height, 0.25 * width, 0.0);
	warrior->initText(manager, "WarriorText", "Warrior");

	std::unique_ptr<UICharStat> archer(new UICharStat(manager, "Archer"));
	archer->init("HUD/Black", "HUD/Green", width, height, 0.25 * width * 2.0, 0.0);
	archer->initText(manager, "ArcherText", "Archer");

	std::unique_ptr<UICharStat> valkyrie(new UICharStat(manager, "Valkyrie"));
	valkyrie->init("HUD/Black", "HUD/Blue", width, height, 0.25 * width * 3.0, 0.0);
	valkyrie->initText(manager, "ValkyrieText", "Valkyrie");

	stats->addChild(wizzard->getPanel());
	stats->addChild(warrior->getPanel());
	stats->addChild(archer->getPanel());
	stats->addChild(valkyrie->getPanel());
	overlay->add2D(stats);

	chars["Wizzard"] = std::move(wizzard);
	chars["Warrior"] = std::move(warrior);
	chars["Archer"] = std::move(archer);
	chars["Valkyrie"] = std::move(valkyrie);
}

bool UIOverlayHUD::mousePressed(Ogre::Real, Ogre::Real) {

	return true;
}

void UIOverlayHUD::registerCallbackByName(Ogre::String const &, std::function<void(void)>) {
}

void UIOverlayHUD::updateScoreByName(Ogre::String const &name, int score) {

	chars[name]->updateScore(name, score);
}

void UIOverlayHUD::updateHealthByName(Ogre::String const &name, int health) {

	chars[name]->updateHealth(name, health);
}
