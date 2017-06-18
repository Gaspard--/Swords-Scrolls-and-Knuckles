#include "UIOverlayStart.hpp"

UIOverlayStart::UIOverlayStart(Renderer &)
  : UIOverlay("start")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "StartBG"))
  , logo(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "StartLogo"))
  , title(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "StartTitle"))
  , pressTxt(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "StartPress"))
{
  std::clog << "Init Overlay Start." << std::endl;
  
  bg->setMaterialName("HUD/HurricaneLogo");
  
  logo->setDimensions(UIOverlayStart::LOGO_WIDTH, UIOverlayStart::LOGO_HEIGHT);
  logo->setPosition(0.5f - UIOverlayStart::LOGO_WIDTH / 2.f, 0.5f - UIOverlayStart::LOGO_HEIGHT / 2.f);
  logo->setMaterialName("HUD/GameLogo");
  logo->hide();
  
  bg->addChild(logo.get());
  bg->addChild(title.get());
  bg->addChild(pressTxt.get());
  
  overlay->add2D(bg.get());
}

void UIOverlayStart::switchBG(void) {

  bg->setMaterialName("HUD/Black");
  logo->show();
	
  initText(title, "PRESENTS", (Ogre::Real)Game::WIDTH / 2.0, 75.0);
  initText(pressTxt, "Press space to start", (Ogre::Real)Game::WIDTH / 2.0, 925.0);
}

void UIOverlayStart::update(void) {

  static int timer(150);
  
	if (timer > 0) {
		--timer;
	}
  
  if (timer == 0) {
    switchBG();
  } else {
		updateText();
	}
}

void UIOverlayStart::initText(UIOverlayResource<Ogre::TextAreaOverlayElement> &txt,
    Ogre::DisplayString const &str, Ogre::Real x, Ogre::Real y) {

  txt->setFontName("HUD/FontPA");
  txt->setCaption(str);
  txt->setMetricsMode(Ogre::GMM_PIXELS);
  txt->setCharHeight(150);
  txt->setPosition(x, y);
  txt->setAlignment(Ogre::TextAreaOverlayElement::Center);
}

void UIOverlayStart::updateText(void) {

  static int timer(0);
  
  ++timer;
  if (timer % 60 > 30) {
    (pressTxt->isVisible()) ? pressTxt->hide() : pressTxt->show();
  }
}
