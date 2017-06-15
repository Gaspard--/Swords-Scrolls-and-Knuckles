#include "UIOverlay.hpp"
#include "UIButton.hpp"

// UIButton

UIButton::UIButton(Ogre::OverlayManager *manager, Ogre::String const &name, std::function<void(void)> const &cb)
  : panel(manager->createOverlayElement("Panel", name))
  , hoverPanel(manager->createOverlayElement("Panel", panel->getName() + "Hover"))
  , callback(cb)
{}

void UIButton::init(
  Ogre::String const &materialName,
  Ogre::Real x,
  Ogre::Real y
)
{
  panel->setDimensions(UIButton::WIDTH, UIButton::HEIGHT);
  panel->setPosition(x, y);
  panel->setMaterialName(materialName);
  
  hoverPanel->setDimensions(UIButton::WIDTH - 0.012f * 2.f, UIButton::HEIGHT);
  hoverPanel->setPosition(0.012f, 0);
  hoverPanel->setMaterialName("HUD/ButtonHovered");
  hoverPanel->hide();
  panel->addChild(hoverPanel.get());
}

Ogre::PanelOverlayElement *UIButton::getPanel(void) const {
  return panel.get();
}

std::function<void(void)> const &UIButton::getCallback(void) const
{
  return (callback);
}

void UIButton::setHovered(bool b)
{
  if (b)
    hoverPanel->show();
  else
    hoverPanel->hide();
}
