#include "SceneMainMenu.hpp"
#include "UIOverlayOptions.hpp"

UIOverlayOptions::UIOverlayOptions(Renderer &renderer)
  : UIOverlay("mainmenu", UIOverlay::Direction::HORIZONTAL)
  , bg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "SelectBG"))
{
  std::clog << "Init Options Menu" << std::endl;

  Ogre::OverlayManager *manager(Ogre::OverlayManager::getSingletonPtr());

  // Background
  bg->setMaterialName("HUD/OptionsMenuBG");
  overlay->add2D(bg.get());

  // Exit button
  std::unique_ptr<UIButton> exit(new UIButton(manager, "Exit", [&renderer]() {
    renderer.switchScene([&renderer]() {
      return static_cast<Scene *>(new SceneMainMenu(renderer));
    });
  }));
  exit->init("HUD/ButtonExit", (1.f - UIButton::DEFAULT_WIDTH) / 2.f, 0.8f);
  bg->addChild(exit->getPanel());
  buttons.emplace_back(std::move(exit));

  constexpr Ogre::Real rposX(0.2f);
  constexpr Ogre::Real posX(Game::WIDTH * rposX);
  constexpr Ogre::Real rposY(0.25f);
  constexpr Ogre::Real posY(Game::HEIGHT * rposY);

  // Options
  for (size_t i = 0; i < renderer.getOptions().size(); i++)
  {
    optionsTxt.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", std::string("Options_") + std::to_string(i)));

    Ogre::TextAreaOverlayElement &gp(*optionsTxt.back().get());
    Option &opt = renderer.getOptions()[i];
    Ogre::Real optY(posY + Game::HEIGHT * UIOverlayOptions::OPTIONSBUTTON_WIDTH * i);
    Ogre::Real rptY(optY / Game::HEIGHT);

    gp.setFontName("HUD/Font");
    gp.setColour(Ogre::ColourValue::White);
    gp.setCaption(opt.getName());
    gp.setMetricsMode(Ogre::GMM_PIXELS);
    gp.setPosition(posX, optY);
    gp.setCharHeight(30.f);
    gp.setAlignment(Ogre::TextAreaOverlayElement::Left);
    bg->addChild(optionsTxt.back().get());

    // Yes/No button
     std::unique_ptr<UIButton> yes(new UIButton(manager, std::string("Yes_") + std::to_string(i), [this, &renderer, i]() {
       renderer.getOptions()[i].setOption(!renderer.getOptions()[i].isActivated());
       updateSelectedOptions(renderer);
     }, UIOverlayOptions::OPTIONSBUTTON_WIDTH, UIOverlayOptions::OPTIONSBUTTON_HEIGHT, 0.f));
     yes->init("HUD/YesButton", rposX + 0.3f, rptY - UIOverlayOptions::OPTIONSBUTTON_HEIGHT * 0.5f + 0.01f);
     bg->addChild(yes->getPanel());
     buttons.emplace_back(std::move(yes));
  }
  updateSelectedOptions(renderer);
}

void UIOverlayOptions::updateSelectedOptions(Renderer &renderer) {
  for (size_t i = 0; i < renderer.getOptions().size() && (i + 1) < buttons.size(); i++) {
    Option &opt = renderer.getOptions()[i];
    UIButton &button = *buttons[i + 1].get();

    button.getPanel()->setMaterialName(opt.isActivated() ? "HUD/YesButton" : "HUD/NoButton");
  }
}
