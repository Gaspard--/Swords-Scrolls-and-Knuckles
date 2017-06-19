#ifndef UIOVERLAY_SCOREBOARD_HPP
# define UIOVERLAY_SCOREBOARD_HPP

# include "UIOverlay.hpp"
# include "Scoreboard.hpp"

class UIOverlayScoreboard : public UIOverlay {
private:
  UIOverlayResource<Ogre::PanelOverlayElement> bg;
  std::vector<UIOverlayResource<Ogre::PanelOverlayElement>> portraits;
  std::vector<UIOverlayResource<Ogre::TextAreaOverlayElement>> scores;
  UIOverlayResource<Ogre::TextAreaOverlayElement> noScore;
  Scoreboard scoreboard;

public:
  UIOverlayScoreboard(void) = delete;
  UIOverlayScoreboard(Renderer &);
  UIOverlayScoreboard(UIOverlayScoreboard const &) = delete;
  UIOverlayScoreboard(UIOverlayScoreboard &&) = delete;
  UIOverlayScoreboard &operator=(UIOverlayScoreboard const &) = delete;
  UIOverlayScoreboard &operator=(UIOverlayScoreboard &&) = delete;
  virtual ~UIOverlayScoreboard(void) = default;
};

#endif // !UIOVERLAY_SCOREBOARD_HPP
