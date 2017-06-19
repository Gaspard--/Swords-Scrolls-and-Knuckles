#include "UIOverlayHUD.hpp"
#include "UIChar.hpp"

char const *UIChar::PORTRAITS_HUD[] =
{
  "HUD/PortraitSylvanas",
  "HUD/PortraitJaina",
  "HUD/PortraitMuradin",
  "HUD/PortraitThrall",
};

static char const *SPELLS_HUD[4][3] =
{
  {
    "HUD/Sylvanas/Spell1",
    "HUD/Sylvanas/Spell2",
    "HUD/Sylvanas/Spell3",
  },
  {
    "HUD/Jaina/Spell1",
    "HUD/Jaina/Spell2",
    "HUD/Jaina/Spell3",
  },
  {
    "HUD/Muradin/Spell1",
    "HUD/Muradin/Spell2",
    "HUD/Muradin/Spell3",
  },
  {
    "HUD/Thrall/Spell1",
    "HUD/Thrall/Spell2",
    "HUD/Thrall/Spell3",
  },
};

UIChar::UIChar(UIOverlayHUD &hud, size_t idx)
  : idx(idx)
  , statBg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "StatBg_" + idx))
  , spellBg(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "SpellBg_" + idx))
  , healthBarEmpty(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "HealthBarEmpty_" + idx))
  , healthBarFull(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "HealthBarFull_" + idx))
  , portrait(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "Portrait_" + idx))
  , coinIcon(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "CoinIcon_" + idx))
  , keyIcon(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "KeyIcon_" + idx))
  , score(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "Score_" + idx))
{
  Ogre::Real posX(0.5f - 2.f * UIChar::STATBG_WIDTH + idx * UIChar::STATBG_WIDTH);

  statBg->setMaterialName("HUD/StatBG");
  statBg->setDimensions(UIChar::STATBG_WIDTH, UIChar::STATBG_HEIGHT);
  statBg->setPosition(posX, 1.f - UIChar::STATBG_HEIGHT);

  spellBg->setMaterialName("HUD/SpellBG");
  spellBg->setDimensions(UIChar::SPELLBG_WIDTH, UIChar::SPELLBG_HEIGHT);
  spellBg->setPosition(posX, 1.f - UIChar::STATBG_HEIGHT - UIChar::SPELLBG_HEIGHT);

  healthBarEmpty->setMaterialName("HUD/HealthBarEmpty");
  healthBarEmpty->setDimensions(UIChar::HEALTHBAR_WIDTH, UIChar::HEALTHBAR_HEIGHT);
  healthBarEmpty->setPosition(posX + UIChar::HEALTHBAR_X_OFFSET, 1.f - UIChar::STATBG_HEIGHT + UIChar::HEALTHBAR_Y_OFFSET);

  healthBarFull->setMaterialName("HUD/HealthBarFull");
  healthBarFull->setDimensions(UIChar::HEALTHBAR_WIDTH, UIChar::HEALTHBAR_HEIGHT);
  healthBarFull->setPosition(posX + UIChar::HEALTHBAR_X_OFFSET, 1.f - UIChar::STATBG_HEIGHT + UIChar::HEALTHBAR_Y_OFFSET);

  portrait->setMaterialName(Ogre::String(PORTRAITS_HUD[idx]));
  portrait->setDimensions(UIChar::PORTRAITBG_WIDTH, UIChar::PORTRAITBG_HEIGHT);
  portrait->setPosition(posX + UIChar::PORTRAIT_X_OFFSET, 1.f - UIChar::STATBG_HEIGHT + UIChar::PORTRAIT_Y_OFFSET);

  keyIcon->setMaterialName("HUD/KeyIcon");
  keyIcon->setDimensions(UIChar::KEYICON_WIDTH, UIChar::KEYICON_HEIGHT);
  keyIcon->setPosition(posX + UIChar::KEYICON_X_OFFSET, 1.f - UIChar::KEYICON_Y_OFFSET);

  coinIcon->setMaterialName("HUD/CoinIcon");
  coinIcon->setDimensions(UIChar::COINICON_WIDTH, UIChar::COINICON_HEIGHT);
  coinIcon->setPosition(posX + UIChar::COINICON_X_OFFSET, 1.f - UIChar::COINICON_Y_OFFSET);

  score->setFontName("HUD/Font");
  score->setCaption("");
  score->setColour(Ogre::ColourValue::White);
  score->setMetricsMode(Ogre::GMM_PIXELS);
  score->setPosition(145.f, 214.f);
  score->setCharHeight(25.f);
  score->setAlignment(Ogre::TextAreaOverlayElement::Right);
  score->show();

  hud.getOverlay()->add2D(statBg.get());
  hud.getOverlay()->add2D(spellBg.get());
  hud.getOverlay()->add2D(healthBarEmpty.get());
  hud.getOverlay()->add2D(healthBarFull.get());
  hud.getOverlay()->add2D(portrait.get());
  hud.getOverlay()->add2D(coinIcon.get());
  hud.getOverlay()->add2D(keyIcon.get());

  for (size_t i = 0; i < 3; i++) {
    spells.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", std::string("Spell") + std::to_string(i) + std::string("_") + std::to_string(idx)));
    spellGreyBG.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", std::string("Spell") + std::to_string(i) + std::string("CB_") + std::to_string(idx)));
    spellCD.emplace_back(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", std::string("Spell") + std::to_string(i) + std::string("GreyGB_") + std::to_string(idx)));

    Ogre::PanelOverlayElement &spell(*spells.back().get());
    Ogre::PanelOverlayElement &greyBG(*spellGreyBG.back().get());
    Ogre::TextAreaOverlayElement &textCD(*spellCD.back().get());

    spell.setMaterialName(Ogre::String(SPELLS_HUD[idx][i]));
    spell.setDimensions(UIChar::SPELL_WIDTH, UIChar::SPELL_HEIGHT);
    spell.setPosition(posX + UIChar::SPELL_X_OFFSET + UIChar::SPELL_X_OFFSETWIDTH * i, 1.f - UIChar::STATBG_HEIGHT - UIChar::SPELLBG_HEIGHT + UIChar::SPELL_Y_OFFSET);
    greyBG.setMaterialName("HUD/SpellHovered");
    greyBG.setDimensions(UIChar::SPELL_WIDTH, UIChar::SPELL_HEIGHT);
    greyBG.setPosition(0, 0);

    textCD.setFontName("HUD/Font");
    textCD.setCaption("");
    textCD.setColour(Ogre::ColourValue::White);
    textCD.setMetricsMode(Ogre::GMM_PIXELS);
    textCD.setPosition(25.f, 8.f);
    textCD.setCharHeight(30.f);
    textCD.setAlignment(Ogre::TextAreaOverlayElement::Center);

    hud.getOverlay()->add2D(spells.back().get());
    spell.addChild(spellGreyBG.back().get());
    greyBG.addChild(spellCD.back().get());
  }

  statBg->addChild(score.get());

  defaultCharUI();
}

void UIChar::updateValues(Player const &p) {
  float percent(static_cast<Ogre::Real>(p.getHealth()) / static_cast<Ogre::Real>(p.getMaxHealth()));
  healthBarFull->setDimensions(UIChar::HEALTHBAR_WIDTH * percent, UIChar::HEALTHBAR_HEIGHT);
  score->setCaption(std::to_string(p.getGold()));
  for (size_t i = 0; i < spells.size(); i++) {
    auto &spell(spells[i]);
    auto &greyBG(spellGreyBG[i]);
    auto &textCD(spellCD[i]);

    int cd(p.getSpellTimeleft(i));
    spell->show();
    if (cd == 0) {
      greyBG->hide();
    }
    else {
      greyBG->show();
      textCD->setCaption(std::to_string(cd));
    }
  }
}

void UIChar::setCharLayout(Player const &p) {
  portrait->setMaterialName(Ogre::String(PORTRAITS_HUD[p.getId()]));
  healthBarFull->show();
  portrait->show();
  score->show();
  coinIcon->show();
  keyIcon->show();
  for (size_t i = 0; i < 3; i++) {
    spells[i]->setMaterialName(Ogre::String(SPELLS_HUD[p.getId()][i]));
  }
}

void UIChar::defaultCharUI(void) {
  healthBarFull->hide();
  portrait->hide();
  score->hide();
  coinIcon->hide();
  keyIcon->hide();
  for (auto &s : spells)
    s->hide();
}
