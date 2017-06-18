#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include <OgreManualObject.h>
#include "UIOverlaySelection.hpp"
#include "LevelScene.hpp"
#include "SceneMainMenu.hpp"
#include "EntityFactory.hpp"
#include "Game.hpp"

UIOverlaySelection::UIOverlaySelection(Renderer &renderer)
  : UIOverlay("mainmenu")
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "SelectBG"))
  , selected(0)
  , cameraNode([&renderer]()
	       {
		 auto cameraNode(renderer.getSceneManager().getRootSceneNode()->createChildSceneNode());

		 cameraNode->attachObject(&renderer.getCamera());
		 cameraNode->setPosition(Ogre::Vector3(10, 0, 0));
		 cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
		 renderer.getCamera().setNearClipDistance(5);
		 return cameraNode;
	       }())
{
  std::clog << "Init Overlay Menu" << std::endl;

  Ogre::OverlayManager *manager(Ogre::OverlayManager::getSingletonPtr());
  constexpr Ogre::Real bwidth(UIOverlaySelection::SELECTIONBUTTON_WIDTH);
  constexpr Ogre::Real posY(0.9f);
  constexpr Ogre::Real posX((0.5f - bwidth) );

  // Background
  bg->setMaterialName("HUD/SelectionMenuBG");

  renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

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
  
  // Adding heroes

  for (size_t i = 0; i < 4; i++) {
    heroes.emplace_back(renderer, HEROES_SKINS[i][0]);
    setHeroDefault(heroes.back(), i);
  }
  setSelectedButton(0);
}

void UIOverlaySelection::updateUI(Ogre::Real x) {
  for (auto &ae : heroes) {
    ae.updateAnimations(x);
  }
}

void UIOverlaySelection::setHeroDefault(AnimatedEntity &ae, size_t i) {
  static constexpr std::array<Ogre::Real, 4> pos{ 5.5f, 1.8f, -1.8f, -5.5f };
  static constexpr std::array<Vect<2, Ogre::Real>, 4> dir{ Vect<2, Ogre::Real>({-1.f, 0.3f}), {-0.9f, 0.4f}, {-0.9f, -0.4f}, {-1.f, -0.3f} };

  ae.getEntity().getNode()->setPosition(0.f, -2.f, pos[i]);
  ae.getEntity().getNode()->setDirection(dir[i][0], 0.f, dir[i][1]);
  ae.getEntity().getNode()->scale(1.f / 100.f, 1.f / 100.f, 1.f / 100.f);
  ae.getEntity().getOgre()->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
  ae.setMainAnimation(Animations::Controllable::STAND, 0.1f);
  ae.updateAnimations(0.1f);
}

void UIOverlaySelection::changeSkin(Renderer &r, bool b) {
  heroes[selected] = AnimatedEntity(r, HEROES_SKINS[selected][b]);
  setHeroDefault(heroes[selected], selected);
}

void UIOverlaySelection::changeSelection(bool b) {
  int i = static_cast<int>(selected) - 1 + b * 2;
  if (i < 0)
    i = heroes.size() + i;
  i %= heroes.size();
  selected = static_cast<size_t>(i);
}
