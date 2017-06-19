#include "UIOverlay.hpp"
#include "UIButton.hpp"

// UIButton

UIButton::UIButton(Ogre::OverlayManager *manager, Ogre::String const &name, std::function<void(void)> const &cb, Ogre::Real w, Ogre::Real h, Ogre::Real o)
  : panel(manager->createOverlayElement("Panel", name))
  , hoverPanel(manager->createOverlayElement("Panel", panel->getName() + "Hover"))
  , callback(cb)
  , width(w)
  , height(h)
  , offset(o)
{}

void UIButton::init(
  Ogre::String const &materialName,
  Ogre::Real x,
  Ogre::Real y
)
{
  panel->setDimensions(width, height);
  panel->setPosition(x, y);
  panel->setMaterialName(materialName);
  
  hoverPanel->setDimensions(width - offset * 2, height);
  hoverPanel->setPosition(offset, 0);
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
