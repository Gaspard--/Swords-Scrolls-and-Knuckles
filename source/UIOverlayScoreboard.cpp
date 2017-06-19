#include "UIChar.hpp"
#include "UIOverlayScoreboard.hpp"

UIOverlayScoreboard::UIOverlayScoreboard(Renderer &renderer)
  : UIOverlay("scoreboard")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "ScoreboardBG"))
  , scoreboard()
{
  Ogre::OverlayManager *manager(Ogre::OverlayManager::getSingletonPtr());

  bg->setMaterialName("HUD/ScoreboardBG");

  for (size_t i = 0; i < 14 && i < scoreboard.getScores().size(); i++) {
    portraits.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", std::string("Portrait") + std::to_string(i)));
    scores.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", std::string("Scores") + std::to_string(i)));
    Ogre::TextAreaOverlayElement &score(*scores.back().get());
    Ogre::PanelOverlayElement &portrait(*portraits.back().get());

    portrait.setMaterialName(Ogre::String(UIChar::PORTRAITS_HUD[static_cast<unsigned int>(scoreboard.getScores()[i].playerClass)]));
    portrait.setDimensions(100.f / Game::WIDTH, 100.f / Game::HEIGHT);
    portrait.setPosition(0.1f + 0.5f * (i >= 7), 0.2f + (i % 7) * 0.110f);

    score.setFontName("HUD/Font");
    score.setCaption(std::to_string(scoreboard.getScores()[i].playerScore));
    score.setColour(Ogre::ColourValue::White);
    score.setMetricsMode(Ogre::GMM_PIXELS);
    score.setPosition(120.f, 35.f);
    score.setCharHeight(50.f);
    score.setAlignment(Ogre::TextAreaOverlayElement::Left);

    bg->addChild(portraits.back().get());
    portrait.addChild(scores.back().get());
  }
  overlay->add2D(bg.get());
  setSelectedButton(0);
}
