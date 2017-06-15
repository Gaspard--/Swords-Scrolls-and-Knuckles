#include "UIOverlay.hpp"
#include "UIButton.hpp"

// UIButton

UIButton::UIButton(Ogre::OverlayManager *manager, Ogre::String const &name, std::function<void(void)> const &cb)
  : panel(static_cast<Ogre::PanelOverlayElement *>(manager->createOverlayElement("Panel", name)))
  , callback(cb)
{}

void UIButton::init(Ogre::OverlayManager *manager,
  Ogre::String const &materialName,
  Ogre::Real x,
  Ogre::Real y
)
{
  panel->setDimensions(UIButton::WIDTH, UIButton::HEIGHT);
  panel->setPosition(x, y);
  panel->setMaterialName(materialName);
}

UIButton::~UIButton(void)
{
  Ogre::OverlayManager::getSingleton().destroyOverlayElement(panel);
}

Ogre::PanelOverlayElement *UIButton::getPanel(void) const {

  return panel;
}

std::function<void(void)> const &UIButton::getCallback(void) const
{
  return (callback);
}
