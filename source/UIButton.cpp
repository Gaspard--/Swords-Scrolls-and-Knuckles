#include "UIOverlay.hpp"
#include "UIButton.hpp"

// UIButton

UIButton::UIButton(Ogre::OverlayManager *manager, Ogre::String const &name, std::function<void(void)> const &cb)
  : panel(static_cast<Ogre::BorderPanelOverlayElement *>(manager->createOverlayElement("BorderPanel", name)))
  , text(static_cast<Ogre::TextAreaOverlayElement *>(manager->createOverlayElement("TextArea", panel->getName() + "Text")))
  , callback(cb)
{}

void UIButton::init(Ogre::OverlayManager *manager,
  Ogre::String const &materialName,
  Ogre::String const &borderName,
  Ogre::Real width,
  Ogre::Real height,
  Ogre::Real x,
  Ogre::Real y
)
{

  panel->setMaterialName(materialName);
  panel->setDimensions(width, height);
  panel->setPosition(x, y);

  panel->setBorderMaterialName(borderName);
  panel->setBorderSize(0.0075f);

  Ogre::Vector2 buttonSize(UIOverlay::relativeToPixels({ panel->getWidth(), panel->getHeight() }));

  text->setFontName("HUD/Font");

  std::string name(panel->getName());
  std::transform(name.begin(), name.end(), name.begin(), ::toupper);
  text->setCaption(name);

  text->setColour(Ogre::ColourValue::White);
  text->setMetricsMode(Ogre::GMM_PIXELS);
  text->setCharHeight(50.f);
  text->setLeft(buttonSize.x / 2.0f);
  text->setTop(buttonSize.y / 2.0f - text->getCharHeight() / 2.f);
  text->setAlignment(Ogre::TextAreaOverlayElement::Center);

  panel->addChild(text);
}

UIButton::~UIButton(void)
{
  Ogre::OverlayManager::getSingleton().destroyOverlayElement(text);
  Ogre::OverlayManager::getSingleton().destroyOverlayElement(panel);
}

Ogre::BorderPanelOverlayElement *UIButton::getPanel(void) const {

  return panel;
}

std::function<void(void)> const &UIButton::getCallback(void) const
{
  return (callback);
}
