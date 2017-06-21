#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include <OgreManualObject.h>
#include "UIOverlaySelection.hpp"
#include "LevelScene.hpp"
#include "SceneMainMenu.hpp"
#include "EntityFactory.hpp"
#include "Game.hpp"
#include "MusicThread.hpp"

char const *UIOverlaySelection::GAMEPLAYS_NAME[] =
{
  "KEYBOARD",
  "JOYSTICK",
  "IA",
  "NONE",
};

Skins::Skin UIOverlaySelection::HEROES_SKINS[4][2] =
{
  { Skins::Archer::BASE, Skins::Archer::HIGH_ELF },
  { Skins::Mage::BASE, Skins::Mage::CLAUS },
  { Skins::Warrior::BASE, Skins::Warrior::RED },
  { Skins::Tank::BASE, Skins::Tank::MAGNI },
};

UIOverlaySelection::UIOverlaySelection(Renderer &renderer)
  : UIOverlay("mainmenu", UIOverlay::Direction::HORIZONTAL)
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "SelectBG"))
  , selected(0)
  , skins()
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
  constexpr Ogre::Real posX((0.5f - bwidth));

  // Background
  bg->setMaterialName("HUD/SelectionMenuBG");
  overlay->add2D(bg.get());

  renderer.getSceneManager().setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

  // Adding heroes

  for (size_t i = 0; i < (int)Gameplays::SIZE; i++) {
    gameplays.emplace_back(i == 0 ? Gameplays::KEYBOARD : Gameplays::NONE);
    skins.emplace_back(0);
    heroes.emplace_back(renderer, HEROES_SKINS[i][skins[i]]);
    setHeroDefault(heroes.back(), i);
    gameplaysTxt.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", std::string("Gameplay_") + std::to_string(i)));

    Ogre::TextAreaOverlayElement &gp(*gameplaysTxt.back().get());
    gp.setFontName("HUD/Font");
    gp.setColour(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    gp.setMetricsMode(Ogre::GMM_PIXELS);
    gp.setPosition(250.f + 473.f * i, 190.f);
    gp.setCharHeight(30.f);
    gp.setAlignment(Ogre::TextAreaOverlayElement::Center);
    renderGameplayName(i);
    bg->addChild(gameplaysTxt.back().get());
  }
  changeSelection(false);
  changeSelection(true);

  // Cancel button
  std::unique_ptr<UIButton> cancel(new UIButton(manager, "Cancel", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return static_cast<Scene *>(new SceneMainMenu(renderer));
    });
  }, bwidth, UIOverlaySelection::SELECTIONBUTTON_HEIGHT, 0.0f));
  cancel->init("HUD/ButtonSelectionCancel", (1.f - bwidth) / 2.f - posX, posY);
  bg->addChild(cancel->getPanel());
  buttons.emplace_back(std::move(cancel));

  // Play button
  std::unique_ptr<UIButton> play(new UIButton(manager, "Play", [this, &renderer]() {
    auto skin(skins);
    auto gps(gameplays);
    renderer.switchScene([&renderer, skin, gps]() {
      std::vector<std::function<AnimatedEntity(Renderer &)>> v;
      std::vector<PlayerId> classes;
      std::vector<Gameplays> gameplays;

      //std::vector<int> s(skins);
      for (size_t i = 0; i < skin.size(); i++) {
	if (gps[i] != Gameplays::NONE) {
	  gameplays.emplace_back(gps[i]);
	  switch (i) {
	  case 0:
	    v.emplace_back([&skin, i](Renderer &renderer) {
	      EntityFactory ef(renderer);
	      return (ef.spawnArcher(UIOverlaySelection::HEROES_SKINS[i][skin[i]]));
	    });
	    classes.emplace_back(PlayerId::ARCHER);
	    break;
	  case 1:
	    v.emplace_back([&skin, i](Renderer &renderer) {
	      EntityFactory ef(renderer);
	      return (ef.spawnMage(UIOverlaySelection::HEROES_SKINS[i][skin[i]]));
	    });
	    classes.emplace_back(PlayerId::MAGE);
	    break;
	  case 2:
	    v.emplace_back([&skin, i](Renderer &renderer) {
	      EntityFactory ef(renderer);
	      return (ef.spawnWarrior(UIOverlaySelection::HEROES_SKINS[i][skin[i]]));
	    });
	    classes.emplace_back(PlayerId::WARRIOR);
	    break;
	  default:
	    v.emplace_back([&skin, i](Renderer &renderer) {
	      EntityFactory ef(renderer);
	      return (ef.spawnTank(UIOverlaySelection::HEROES_SKINS[i][skin[i]]));
	    });
	    classes.emplace_back(PlayerId::TANK);
	    break;
	  }
	}
      }
      AudioSource::playIndependentSound(Sounds::METROID_DOOR);

      MusicThread::getInstance()->setMusic(Musics::SMALL_WORLD);
      MusicThread::getInstance()->play();
      return static_cast<Scene *>(new LevelScene(renderer, v, classes, gameplays));
    });
  }, bwidth, UIOverlaySelection::SELECTIONBUTTON_HEIGHT, 0.0f));
  play->init("HUD/ButtonSelectionPlay", (1.f - bwidth) / 2.f + posX, posY);
  bg->addChild(play->getPanel());
  buttons.emplace_back(std::move(play));

  setSelectedButton(1);
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
  if (gameplays[selected] != Gameplays::NONE) {
    skins[selected] += -1 + b * 2;
    if (skins[selected] < 0)
      skins[selected] = 2 + skins[selected];
    skins[selected] %= 2;
    heroes[selected] = AnimatedEntity(r, HEROES_SKINS[selected][skins[selected]]);
    setHeroDefault(heroes[selected], selected);
  }
}

void UIOverlaySelection::changeSelection(bool b) {
  gameplaysTxt[selected]->setColour(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
  int i = static_cast<int>(selected) - 1 + b * 2;
  if (i < 0)
    i = heroes.size() + i;
  i %= heroes.size();
  selected = static_cast<size_t>(i);
  gameplaysTxt[selected]->setColour(Ogre::ColourValue::White);
}

void UIOverlaySelection::renderGameplayName(size_t i) {
  gameplaysTxt[i]->setCaption(GAMEPLAYS_NAME[static_cast<int>(gameplays[i])]);
  heroes[i].getEntity().getNode()->setVisible(gameplays[i] != Gameplays::NONE);
}

void UIOverlaySelection::changeGameplay(bool b) {
  auto const countKeyboards([this]() {
    size_t i(0);
    for (auto const &g : gameplays) {
      i += (g == Gameplays::KEYBOARD);
    }
    return (i);
  });
  auto const countNone([this]() {
    size_t i(0);
    for (auto const &g : gameplays) {
      i += (g == Gameplays::NONE);
    }
    return (i);
  });

  int i = static_cast<int>(gameplays[selected]);
  i += -1 + 2 * b;
  if (i < 0)
    i = (int)Gameplays::SIZE + i;
  i %= (int)Gameplays::SIZE;
  gameplays[selected] = static_cast<Gameplays>(i);
  if (countKeyboards() >= 3) {
    changeGameplay(b);
  }
  if (countNone() >= 4) {
    changeGameplay(b);
  }
  renderGameplayName(selected);
}
