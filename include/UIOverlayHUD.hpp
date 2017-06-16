#ifndef UIOVERLAYHUD_HPP
# define UIOVERLAYHUD_HPP

# include <vector>
# include <memory>
# include "Player.hpp"
# include "Renderer.hpp"
# include "UIOverlay.hpp"
# include "UIChar.hpp"

class UIOverlayHUD : public UIOverlay {
  std::vector<std::unique_ptr<UIChar>> charPanels;

public:
  UIOverlayHUD(void) = delete;
  UIOverlayHUD(Renderer &);
  UIOverlayHUD(UIOverlayHUD const &) = delete;
  UIOverlayHUD(UIOverlayHUD &&) = delete;
  UIOverlayHUD &operator=(UIOverlayHUD const &) = delete;
  UIOverlayHUD &operator=(UIOverlayHUD &&) = delete;
  virtual ~UIOverlayHUD(void) = default;

  void updateHUD(std::vector<Player> const &);
};

#endif // !UIOVERLAYHUD_HPP
