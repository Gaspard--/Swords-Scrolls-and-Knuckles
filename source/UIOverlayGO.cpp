#include "UIOverlayGO.hpp"

UIOverlayGO::UIOverlayGO(Renderer &renderer)
  : UIOverlay("gameover")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "GameOverBG"))
{
  std::clog << "Init Overlay Game Over" << std::endl;

  Ogre::OverlayManager *manager(Ogre::OverlayManager::getSingletonPtr());
  int i(0);
  Ogre::Real posX(0.5f - BUTTON_WIDTH / 2.f);
  Ogre::Real offset(0.45f);
  Ogre::Real mult(1.6f);

  // Background
  bg->setMaterialName("HUD/GameOverBG");

  // Try again button
  std::unique_ptr<UIButton> tryAgain(new UIButton(manager, "TryAgain", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return static_cast<Scene *>(new SceneSelection(renderer));
    });
  }, BUTTON_WIDTH, BUTTON_HEIGHT, 0.f));
  tryAgain->init("HUD/GOTryAgain", posX, offset + BUTTON_HEIGHT * mult * i++);
  bg->addChild(tryAgain->getPanel());
  buttons.emplace_back(std::move(tryAgain));
	
  // Score button
  std::unique_ptr<UIButton> score(new UIButton(manager, "Score", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return static_cast<Scene *>(new SceneScoreboard(renderer));
    });
  }, BUTTON_WIDTH, BUTTON_HEIGHT, 0.f));
  score->init("HUD/GOScore", posX, offset + BUTTON_HEIGHT * mult * i++);
  bg->addChild(score->getPanel());
  buttons.emplace_back(std::move(score));

  // Exit button
  std::unique_ptr<UIButton> exit(new UIButton(manager, "Exit", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return static_cast<Scene *>(new SceneMainMenu(renderer));
    });
  }, BUTTON_WIDTH, BUTTON_HEIGHT, 0.f));
  exit->init("HUD/GOExit", posX, offset + BUTTON_HEIGHT * mult * i++);
  bg->addChild(exit->getPanel());
  buttons.emplace_back(std::move(exit));
	
  overlay->add2D(bg.get());
  setSelectedButton(0);
}
