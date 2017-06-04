#include "UIOverlayMenu.hpp"

// UIButton

UIButton::UIButton(Ogre::OverlayManager *manager, Ogre::String const &name)
{
	button
		= static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", name));
}

void UIButton::init(Ogre::OverlayManager *manager, Ogre::String const &materialName, Ogre::String const &borderName,
		Ogre::Real width, Ogre::Real height, Ogre::Real x, Ogre::Real y) {

	button->setMaterialName(materialName);
	button->setDimensions(width, height);
	button->setPosition(x, y);

	button->setBorderMaterialName(borderName);
	button->setBorderSize(0.0075);

	Ogre::Vector2 buttonSize(UIOverlay::relativeToPixels({button->getWidth(), button->getHeight()}));

	Ogre::TextAreaOverlayElement *text
		= static_cast<Ogre::TextAreaOverlayElement *>(manager->createOverlayElement("TextArea", button->getName() + "Text"));
	text->setFontName("HUD/Font");

	std::string name(button->getName());
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	text->setCaption(name);

	text->setColour(Ogre::ColourValue::White);
	text->setMetricsMode(Ogre::GMM_PIXELS);
	text->setCharHeight(50);
	text->setLeft(buttonSize.x / 2.0);
	text->setTop(buttonSize.y / 2.0 - text->getCharHeight() / 2);
	text->setAlignment(Ogre::TextAreaOverlayElement::Center);

	button->addChild(text);
}

Ogre::BorderPanelOverlayElement *UIButton::getButton(void) const {

	return button;
}

// UIOverlayMenu

void UIOverlayMenu::init(Ogre::OverlayManager *manager) {

	std::clog << "Overlay Menu init." << std::endl;
	width = 0.5;
	height = 0.1;

	Ogre::PanelOverlayElement *bg
		= static_cast<Ogre::PanelOverlayElement *>(manager->createOverlayElement("Panel", "BG"));
	bg->setMaterialName("HUD/Black");

	std::string gameTitle("SWORDS SCROLLS AND KNUCKLES");
	Ogre::TextAreaOverlayElement *title
		= static_cast<Ogre::TextAreaOverlayElement *>(manager->createOverlayElement("TextArea", "Title"));
	title->setFontName("HUD/Font");
	title->setCaption(gameTitle);
	title->setColour(Ogre::ColourValue::White);
	title->setMetricsMode(Ogre::GMM_PIXELS);
	title->setCharHeight(100);
	title->setLeft(Game::WIDTH / 2- gameTitle.size() / 2);
	title->setTop(40);
	title->setAlignment(Ogre::TextAreaOverlayElement::Center);

	std::unique_ptr<UIButton> play(new UIButton(manager, "Play"));
	play->init(manager, "HUD/Black", "HUD/Green", width, height, 0.5 - width / 2.0, 0.3);

	std::unique_ptr<UIButton> credits(new UIButton(manager, "Credits"));
	credits->init(manager, "HUD/Black", "HUD/Yellow", width, height, 0.5 - width / 2.0, 0.5);

	std::unique_ptr<UIButton> exit(new UIButton(manager, "Exit"));
	exit->init(manager, "HUD/Black", "HUD/Red", width, height, 0.5 - width / 2.0, 0.7);

	bg->addChild(title);
	bg->addChild(play->getButton());
	bg->addChild(credits->getButton());
	bg->addChild(exit->getButton());
	overlay->add2D(bg);

	buttons["Play"] = std::move(play);
	buttons["Credits"] = std::move(credits);
	buttons["Exit"] = std::move(exit);
}

bool UIOverlayMenu::mousePressed(Ogre::Real x, Ogre::Real y) {

	for (auto &&button : buttons) {
		Ogre::BorderPanelOverlayElement *menuButton(button.second->getButton());
		Ogre::Vector2 buttonSize(UIOverlay::relativeToPixels({menuButton->getWidth(),
					menuButton->getHeight()}));
		Ogre::Vector2 buttonPos(UIOverlay::relativeToPixels({menuButton->getLeft(),
					menuButton->getTop()}));
		if (x >= buttonPos.x && x <= buttonPos.x + buttonSize.x
				&& y >= buttonPos.y && y <= buttonPos.y + buttonSize.y) {
			std::clog << menuButton->getName() << " pressed !" << std::endl;
			callbacks[menuButton->getName()]();
		}
	}
	return true;
}

void UIOverlayMenu::registerCallbackByName(Ogre::String const &buttonName,
		std::function<void(void)> func) {

	callbacks[buttonName] = func;
}
