#include "UIOverlayPause.hpp"
#include "SceneMainMenu.hpp"
#include "LevelScene.hpp"

UIOverlayPause::UIOverlayPause(LevelScene &ls, Renderer &renderer)
  : UIOverlay("pausemenu")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "PauseBG"))
{
  std::clog << "Init Overlay Pause" << std::endl;

  Ogre::OverlayManager *manager(Ogre::OverlayManager::getSingletonPtr());
  int i(0);
  Ogre::Real posX(0.55f);
  Ogre::Real offset(0.2f);
  Ogre::Real mult(1.8f);

  // Background
  bg->setMaterialName("HUD/PauseMenuBG");

  // Play button
  std::unique_ptr<UIButton> resume(new UIButton(manager, "Resume", [&ls, &renderer]() {
    ls.unpauseScene(renderer);
  }));
  resume->init("HUD/ButtonPauseResume", posX, offset + UIButton::DEFAULT_HEIGHT * mult * i++);
  bg->addChild(resume->getPanel());
  buttons.emplace_back(std::move(resume));

  // Exit button
  std::unique_ptr<UIButton> save(new UIButton(manager, "Save", [&ls, &renderer]() {
    ls.unpauseScene(renderer);
  }));
  save->init("HUD/ButtonPauseSave", posX, offset + UIButton::DEFAULT_HEIGHT * mult * i++);
  bg->addChild(save->getPanel());
  buttons.emplace_back(std::move(save));

  // Exit button
  std::unique_ptr<UIButton> options(new UIButton(manager, "Options", [&ls, &renderer]() {
    ls.unpauseScene(renderer);
  }));
  options->init("HUD/ButtonPauseOptions", posX, offset + UIButton::DEFAULT_HEIGHT * mult * i++);
  bg->addChild(options->getPanel());
  buttons.emplace_back(std::move(options));

  // Exit button
  std::unique_ptr<UIButton> exit(new UIButton(manager, "Exit", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return new SceneMainMenu(renderer);
    });
  }));
  exit->init("HUD/ButtonPauseExit", posX, offset + UIButton::DEFAULT_HEIGHT * mult * i++);
  bg->addChild(exit->getPanel());
  buttons.emplace_back(std::move(exit));

  overlay->add2D(bg.get());
  overlay->setZOrder(600); // Put the Pause overlay in front of pretty much anything
  setSelectedButton(0);
}
