#include "LevelScene.hpp"
#include "Game.hpp"
#include "UIOverlayMenu.hpp"

UIOverlayMenu::UIOverlayMenu(Renderer &renderer)
  : UIOverlay("mainmenu")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "BG"))
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
    std::clog << "Going to level scene" << std::endl;
    renderer.switchScene([&renderer]() {
      LevelScene::createWallMesh();
      return static_cast<Scene *>(new LevelScene(renderer));
    });
  }));
  play->init("HUD/ButtonPlay", posX, offset + UIButton::HEIGHT * mult * i++);
  bg->addChild(play->getPanel());
  buttons["Play"] = std::move(play);

  // Exit button
  std::unique_ptr<UIButton> load(new UIButton(manager, "Load", []() {
    throw Game::GameQuitException();
  }));
  load->init("HUD/ButtonLoad", posX, offset + UIButton::HEIGHT * mult * i++);
  bg->addChild(load->getPanel());
  buttons["Load"] = std::move(load);

  // Exit button
  std::unique_ptr<UIButton> options(new UIButton(manager, "Options", []() {
    throw Game::GameQuitException();
  }));
  options->init("HUD/ButtonOptions", posX, offset + UIButton::HEIGHT * mult * i++);
  bg->addChild(options->getPanel());
  buttons["Options"] = std::move(options);

  // Exit button
  std::unique_ptr<UIButton> exit(new UIButton(manager, "Exit", []() {
    throw Game::GameQuitException();
  }));
  exit->init("HUD/ButtonExit", posX, offset + UIButton::HEIGHT * mult * i++);
  bg->addChild(exit->getPanel());
  buttons["Exit"] = std::move(exit);

  overlay->add2D(bg.get());
}
