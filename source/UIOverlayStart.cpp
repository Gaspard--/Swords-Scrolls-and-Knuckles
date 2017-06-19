#include <chrono>
#include <ctime>
#include "UIOverlayStart.hpp"

UIOverlayStart::UIOverlayStart(Renderer &)
  : UIOverlay("start")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "StartBG"))
  , pressTxt(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "StartPress"))
  , startTime(std::chrono::system_clock::now())
{
  std::clog << "Init Overlay Start." << std::endl;

  bg->setMaterialName("HUD/HurricaneLogo");

  bg->addChild(pressTxt.get());

  overlay->add2D(bg.get());
}

void UIOverlayStart::switchBG(void) {
  bg->setMaterialName("HUD/GameLogo");
	
  initText(pressTxt, "Press space to start", static_cast<Ogre::Real>(Game::WIDTH / 2.0), 925.0, Ogre::ColourValue::Red);
}

void UIOverlayStart::update(void) {
  std::chrono::time_point<std::chrono::system_clock> time(std::chrono::system_clock::now());
  auto seconds(std::chrono::duration_cast<std::chrono::seconds>(time - startTime).count());
	
  if (seconds == 3) {
    switchBG();
  }
  else {
    updateText();
  }
}

void UIOverlayStart::initText(UIOverlayResource<Ogre::TextAreaOverlayElement> &txt,
  Ogre::DisplayString const &str, Ogre::Real x, Ogre::Real y, Ogre::ColourValue color) {
  txt->setFontName("HUD/FontPA");
  txt->setCaption(str);
  txt->setColour(color);
  txt->setMetricsMode(Ogre::GMM_PIXELS);
  txt->setCharHeight(150);
  txt->setPosition(x, y);
  txt->setAlignment(Ogre::TextAreaOverlayElement::Center);
}

void UIOverlayStart::updateText(void) {

	if (bg->getMaterialName() == "HUD/HurricaneLogo") {
		return ;
	}
	
  if (std::time(nullptr) % 2 == 0) {
		if (!pressTxt->isVisible()) {
		  pressTxt->show();
			initText(pressTxt, "Press space to start", static_cast<Ogre::Real>(Game::WIDTH / 2.0), 925.0, Ogre::ColourValue::Red);
		}
  } else {
		if (pressTxt->isVisible()) {
		  pressTxt->hide();
		}
	}
}
