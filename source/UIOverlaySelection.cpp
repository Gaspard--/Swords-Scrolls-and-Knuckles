#include "UIOverlaySelection.hpp"
#include "LevelScene.hpp"
#include "SceneMainMenu.hpp"
#include "Game.hpp"

UIOverlaySelection::UIOverlaySelection(Renderer &renderer)
  : UIOverlay("mainmenu")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "SelectBG"))
{
  std::clog << "Init Overlay Menu" << std::endl;

  Ogre::OverlayManager *manager(Ogre::OverlayManager::getSingletonPtr());
  constexpr Ogre::Real bwidth(UIOverlaySelection::SELECTIONBUTTON_WIDTH);
  constexpr Ogre::Real posY(0.9f);
  constexpr Ogre::Real posX((0.5f - bwidth) );

  // Background
  bg->setMaterialName("HUD/SelectionMenuBG");

  // Play button
  std::unique_ptr<UIButton> cancel(new UIButton(manager, "Cancel", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return static_cast<Scene *>(new SceneMainMenu(renderer));
    });
  }, bwidth, UIOverlaySelection::SELECTIONBUTTON_HEIGHT, 0.0f));
  cancel->init("HUD/ButtonSelectionCancel",(1.f - bwidth) / 2.f - posX, posY);
  bg->addChild(cancel->getPanel());
  buttons.emplace_back(std::move(cancel));

  // Exit button
  std::unique_ptr<UIButton> play(new UIButton(manager, "Play", [&renderer]() {
    renderer.switchScene([&renderer]() {
      LevelScene::createWallMesh();
      return static_cast<Scene *>(new LevelScene(renderer));
    });
  }, bwidth, UIOverlaySelection::SELECTIONBUTTON_HEIGHT, 0.0f));
  play->init("HUD/ButtonSelectionPlay", (1.f - bwidth) / 2.f + posX, posY);
  bg->addChild(play->getPanel());
  buttons.emplace_back(std::move(play));

  overlay->add2D(bg.get());
  setSelectedButton(0);
}
