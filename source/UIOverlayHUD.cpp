#include "UIOverlayHUD.hpp"

UIOverlayHUD::UIOverlayHUD(Renderer &renderer)
  : UIOverlay("hud")
{
  std::clog << "Init HUD" << std::endl;

  std::unique_ptr<UIChar> player1(new UIChar(*this, 0));
  charPanels.emplace_back(std::move(player1));

  std::unique_ptr<UIChar> player2(new UIChar(*this, 1));
  charPanels.emplace_back(std::move(player2));

  std::unique_ptr<UIChar> player3(new UIChar(*this, 2));
  charPanels.emplace_back(std::move(player3));

  std::unique_ptr<UIChar> player4(new UIChar(*this, 3));
  charPanels.emplace_back(std::move(player4));

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
