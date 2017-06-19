#include "SceneSelection.hpp"
#include "Game.hpp"
#include "UIOverlayMenu.hpp"
#include "UIChar.hpp"

UIOverlayMenu::UIOverlayMenu(Renderer &renderer)
  : UIOverlay("mainmenu")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "BG"))
  , scoreboardTxt(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", std::string("ScoreboardTxt")))
{
  std::clog << "Init Overlay Menu" << std::endl;

  Ogre::OverlayManager *manager(Ogre::OverlayManager::getSingletonPtr());
  int i(0);
  Ogre::Real posX(0.075f);
  Ogre::Real offset(0.35f);
  Ogre::Real mult(1.6f);

  // Background
  bg->setMaterialName("HUD/MainMenuBG");

  // Play button
  std::unique_ptr<UIButton> play(new UIButton(manager, "Play", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return static_cast<Scene *>(new SceneSelection(renderer));
    });
  }));
  play->init("HUD/ButtonPlay", posX, offset + UIButton::DEFAULT_HEIGHT * mult * i++);
  bg->addChild(play->getPanel());
  buttons.emplace_back(std::move(play));

  // Exit button
  std::unique_ptr<UIButton> load(new UIButton(manager, "Load", []() {
    throw Game::GameQuitException();
  }));
  load->init("HUD/ButtonLoad", posX, offset + UIButton::DEFAULT_HEIGHT * mult * i++);
  bg->addChild(load->getPanel());
  buttons.emplace_back(std::move(load));

  // Exit button
  std::unique_ptr<UIButton> options(new UIButton(manager, "Options", []() {
    throw Game::GameQuitException();
  }));
  options->init("HUD/ButtonOptions", posX, offset + UIButton::DEFAULT_HEIGHT * mult * i++);
  bg->addChild(options->getPanel());
  buttons.emplace_back(std::move(options));

  // Exit button
  std::unique_ptr<UIButton> exit(new UIButton(manager, "Exit", []() {
    throw Game::GameQuitException();
  }));
  exit->init("HUD/ButtonExit", posX, offset + UIButton::DEFAULT_HEIGHT * mult * i++);
  bg->addChild(exit->getPanel());
  buttons.emplace_back(std::move(exit));

  overlay->add2D(bg.get());
  setSelectedButton(0);

  // Scoreboard
  scoreboardTxt->setFontName("HUD/Font");
  scoreboardTxt->setCaption("SCOREBOARD");
  scoreboardTxt->setColour(Ogre::ColourValue::White);
  scoreboardTxt->setMetricsMode(Ogre::GMM_PIXELS);
  scoreboardTxt->setPosition(Game::WIDTH * 0.55f, Game::HEIGHT * 0.65f);
  scoreboardTxt->setCharHeight(50.f);
  scoreboardTxt->setAlignment(Ogre::TextAreaOverlayElement::Left);
  bg->addChild(scoreboardTxt.get());

  for (size_t i = 0; i < 4; i++) {

    portraits.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", std::string("Portrait") + std::to_string(i)));
    scores.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", std::string("Scores") + std::to_string(i)));
    Ogre::TextAreaOverlayElement &score(*scores.back().get());
    Ogre::PanelOverlayElement &portrait(*portraits.back().get());

    portrait.setMaterialName(Ogre::String(UIChar::PORTRAITS_HUD[0]));
    portrait.setDimensions(50.f / Game::WIDTH, 50.f / Game::HEIGHT);
    portrait.setPosition(0.5f, 0.7f + i * 0.055f);

    score.setFontName("HUD/Font");
    score.setCaption("12345");
    score.setColour(Ogre::ColourValue::White);
    score.setMetricsMode(Ogre::GMM_PIXELS);
    score.setPosition(60.f, 15.f);
    score.setCharHeight(30.f);
    score.setAlignment(Ogre::TextAreaOverlayElement::Left);

    overlay->add2D(portraits.back().get());
    portrait.addChild(scores.back().get());
  }
}
