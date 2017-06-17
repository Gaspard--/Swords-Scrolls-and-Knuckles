#include "UIOverlayHUD.hpp"

UIOverlayHUD::UIOverlayHUD(Renderer &renderer)
  : UIOverlay("hud")
{
  (void)renderer;
  std::clog << "Init HUD" << std::endl;

  for (std::size_t i = 0; i < 4; i++) {
    std::unique_ptr<UIChar> player(new UIChar(*this, i));
    charPanels.emplace_back(std::move(player));
  }

  std::clog << "Finshed init HUD" << std::endl;
}

void UIOverlayHUD::updateHUD(std::vector<Player> const &v) {
  size_t i;
  for (i = 0; i < v.size() && i < charPanels.size(); i++) {
    charPanels[i]->updateCharUI(v[i]);
  }
  while (i < charPanels.size()) {
    charPanels[i]->defaultCharUI();
    i++;
  }
}
