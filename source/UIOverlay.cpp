#include "UIOverlay.hpp"
#include "Game.hpp"

UIOverlay::UIOverlay(std::string const &name)
  : overlay(Ogre::OverlayManager::getSingleton().create(name))
  , buttons()
{
  overlay->show();
}

UIOverlay::~UIOverlay()
{
  overlay->hide();
  Ogre::OverlayManager::getSingleton().destroy(overlay);
}

Ogre::Overlay *UIOverlay::getOverlay(void) const {
  return overlay;
}

Ogre::Vector2 UIOverlay::pixelsToRelative(Ogre::Vector2 pixels) {
  return Ogre::Vector2(pixels.x / (Ogre::Real)Game::WIDTH, pixels.y / (Ogre::Real)Game::HEIGHT);
}

Ogre::Vector2 UIOverlay::relativeToPixels(Ogre::Vector2 relative) {
  return Ogre::Vector2(relative.x * (Ogre::Real)Game::WIDTH, relative.y * (Ogre::Real)Game::HEIGHT);
}

void UIOverlay::mousePressed(Ogre::Real x, Ogre::Real y)
{
  for (auto &&button : buttons) {
    Ogre::PanelOverlayElement *menuButton(button.second->getPanel());
    Ogre::Vector2 buttonSize(UIOverlay::relativeToPixels({ menuButton->getWidth(),
			    menuButton->getHeight() }));
    Ogre::Vector2 buttonPos(UIOverlay::relativeToPixels({ menuButton->getLeft(),
			    menuButton->getTop() }));
    if (x >= buttonPos.x && x <= buttonPos.x + buttonSize.x
      && y >= buttonPos.y && y <= buttonPos.y + buttonSize.y) {
      buttons[menuButton->getName()]->getCallback()();
    }
  }
}

void UIOverlay::mouseMoved(Ogre::Real x, Ogre::Real y) {
  for (auto &&button : buttons) {
    Ogre::PanelOverlayElement *menuButton(button.second->getPanel());
    Ogre::Vector2 buttonSize(UIOverlay::relativeToPixels({ menuButton->getWidth(),
			    menuButton->getHeight() }));
    Ogre::Vector2 buttonPos(UIOverlay::relativeToPixels({ menuButton->getLeft(),
			    menuButton->getTop() }));
    buttons[menuButton->getName()]->setHovered(
      x >= buttonPos.x
      && x <= buttonPos.x + buttonSize.x
      && y >= buttonPos.y
      && y <= buttonPos.y + buttonSize.y
    );

  }
}
