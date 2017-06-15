#include "SceneMainMenu.hpp"
#include "UIOverlayPause.hpp"

UIOverlayPause::UIOverlayPause(Renderer &renderer)
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
  std::unique_ptr<UIButton> resume(new UIButton(manager, "Resume", [this]() {
    this->getOverlay()->hide();
  }));
  resume->init("HUD/ButtonPauseResume", posX, offset + UIButton::HEIGHT * mult * i++);
  bg->addChild(resume->getPanel());
  buttons["Resume"] = std::move(resume);

  // Exit button
  std::unique_ptr<UIButton> save(new UIButton(manager, "Save", [this]() {
    this->getOverlay()->hide();
  }));
  save->init("HUD/ButtonPauseSave", posX, offset + UIButton::HEIGHT * mult * i++);
  bg->addChild(save->getPanel());
  buttons["Save"] = std::move(save);

  // Exit button
  std::unique_ptr<UIButton> options(new UIButton(manager, "Options", [this]() {
    this->getOverlay()->hide();
  }));
  options->init("HUD/ButtonPauseOptions", posX, offset + UIButton::HEIGHT * mult * i++);
  bg->addChild(options->getPanel());
  buttons["Options"] = std::move(options);

  // Exit button
  std::unique_ptr<UIButton> exit(new UIButton(manager, "Exit", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return new SceneMainMenu(renderer);
    });
  }));
  exit->init("HUD/ButtonPauseExit", posX, offset + UIButton::HEIGHT * mult * i++);
  bg->addChild(exit->getPanel());
  buttons["Exit"] = std::move(exit);

  overlay->add2D(bg.get());
  overlay->setZOrder(600); // Put the Pause overlay in front of pretty much anything
}
