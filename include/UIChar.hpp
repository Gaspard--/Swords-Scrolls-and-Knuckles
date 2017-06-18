#ifndef UICHAR_HPP
# define UICHAR_HPP

# include <vector>
# include <string>
# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreTextAreaOverlayElement.h>
# include "Game.hpp"
# include "UIOverlayResource.hpp"

class UIOverlayHUD;
class Player;

class UIChar {
  size_t idx;
  UIOverlayResource<Ogre::PanelOverlayElement> statBg;
  UIOverlayResource<Ogre::PanelOverlayElement> spellBg;
  UIOverlayResource<Ogre::PanelOverlayElement> healthBarEmpty;
  UIOverlayResource<Ogre::PanelOverlayElement> healthBarFull;
  UIOverlayResource<Ogre::PanelOverlayElement> portrait;
  UIOverlayResource<Ogre::PanelOverlayElement> coinIcon;
  UIOverlayResource<Ogre::PanelOverlayElement> keyIcon;
  UIOverlayResource<Ogre::TextAreaOverlayElement> score;

  std::vector<UIOverlayResource<Ogre::PanelOverlayElement>> spells;
  std::vector<UIOverlayResource<Ogre::PanelOverlayElement>> spellGreyBG;
  std::vector<UIOverlayResource<Ogre::TextAreaOverlayElement>> spellCD;

public:
  static constexpr float STATBG_WIDTH = 173.f / Game::WIDTH;
  static constexpr float STATBG_HEIGHT = 247.f / Game::HEIGHT;

  static constexpr float SPELLBG_WIDTH = 173.f / Game::WIDTH;
  static constexpr float SPELLBG_HEIGHT = 51.f / Game::HEIGHT;

  static constexpr float HEALTHBAR_WIDTH = 165.f / Game::WIDTH;
  static constexpr float HEALTHBAR_HEIGHT = 25.f / Game::HEIGHT;
  static constexpr float HEALTHBAR_X_OFFSET = (STATBG_WIDTH - HEALTHBAR_WIDTH) / 2.f;
  static constexpr float HEALTHBAR_Y_OFFSET = 7.f / Game::HEIGHT;

  static constexpr float KEYICON_WIDTH = 19.f / Game::WIDTH;
  static constexpr float KEYICON_HEIGHT = 23.f / Game::HEIGHT;
  static constexpr float KEYICON_X_OFFSET = 25.f / Game::WIDTH;
  static constexpr float KEYICON_Y_OFFSET = 35.f / Game::HEIGHT;

  static constexpr float COINICON_WIDTH = 25.f / Game::WIDTH;
  static constexpr float COINICON_HEIGHT = 25.f / Game::HEIGHT;
  static constexpr float COINICON_X_OFFSET = 50.f / Game::WIDTH;
  static constexpr float COINICON_Y_OFFSET = 35.f / Game::HEIGHT;
  
  static constexpr float SPELL_WIDTH = 47.f / Game::WIDTH;
  static constexpr float SPELL_HEIGHT = 38.f / Game::HEIGHT;
  static constexpr float SPELL_X_OFFSETWIDTH = 55.f / Game::WIDTH;
  static constexpr float SPELL_X_OFFSET = 8.f / Game::WIDTH;
  static constexpr float SPELL_Y_OFFSET = 6.f / Game::HEIGHT;

  static constexpr float PORTRAITBG_WIDTH = 129.f / Game::WIDTH;
  static constexpr float PORTRAITBG_HEIGHT = 129.f / Game::HEIGHT;
  static constexpr float PORTRAIT_X_OFFSET = 22.f / Game::WIDTH;
  static constexpr float PORTRAIT_Y_OFFSET = 54.f / Game::HEIGHT;

  UIChar(UIOverlayHUD &, size_t id);
  UIChar(UIChar const &) = delete;
  UIChar(UIChar &&) = delete;
  UIChar &operator=(UIChar const &) = delete;
  UIChar &operator=(UIChar &&) = delete;
  virtual ~UIChar(void) = default;

  void setCharLayout(Player const &p);
  void updateValues(Player const &p);
  void defaultCharUI(void);
};

#endif // !UICHAR_HPP
