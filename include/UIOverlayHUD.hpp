#ifndef UIOVERLAYHUD_HPP
# define UIOVERLAYHUD_HPP

# include <memory>
# include <unordered_map>
# include <Overlay/OgreTextAreaOverlayElement.h>
# include <Overlay/OgrePanelOverlayElement.h>
# include <Overlay/OgreBorderPanelOverlayElement.h>
# include "Renderer.hpp"
# include "UIOverlay.hpp"
# include "UIChar.hpp"

class UICharStat {
private:
  Ogre::BorderPanelOverlayElement *panel;
  Ogre::TextAreaOverlayElement *text;
  Ogre::TextAreaOverlayElement *scoreTxt;
  Ogre::TextAreaOverlayElement *healthTxt;

  void setText(
    Ogre::TextAreaOverlayElement *,
    Ogre::DisplayString const &,
    Ogre::Vector2, Ogre::Vector2, Ogre::Real
  );

public:
  UICharStat(Ogre::OverlayManager *, Ogre::String const &);
  UICharStat(UICharStat const &) = delete;
  UICharStat(UICharStat &&) = delete;
  UICharStat &operator=(UICharStat const &) = delete;
  UICharStat &operator=(UICharStat &&) = delete;
  virtual ~UICharStat(void);

  void init(Ogre::String const &, Ogre::String const &,
    Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real);
  void initText(Ogre::OverlayManager *, Ogre::String const &, Ogre::DisplayString const &);

  void updateScore(Ogre::String const &, int);
  void updateHealth(Ogre::String const &, int);

  Ogre::BorderPanelOverlayElement *getPanel(void) const;

};

class UIOverlayHUD : public UIOverlay {
public:
  UIOverlayHUD(void) = delete;
  UIOverlayHUD(Renderer &);
  UIOverlayHUD(UIOverlayHUD const &) = delete;
  UIOverlayHUD(UIOverlayHUD &&) = delete;
  UIOverlayHUD &operator=(UIOverlayHUD const &) = delete;
  UIOverlayHUD &operator=(UIOverlayHUD &&) = delete;
  virtual ~UIOverlayHUD(void);

  void updateScoreByName(Ogre::String const &, int);
  void updateHealthByName(Ogre::String const &, int);

private:
  Ogre::Real width;
  Ogre::Real height;
  std::unordered_map<Ogre::String, std::unique_ptr<UICharStat>> chars;
  Ogre::PanelOverlayElement *stats;
};

#endif // !UIOVERLAYHUD_HPP
