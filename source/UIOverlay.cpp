#include "UIOverlay.hpp"
#include "Game.hpp"

UIOverlay::UIOverlay(std::string const &name, enum class Direction dir)
  : overlay(Ogre::OverlayManager::getSingleton().create(name))
  , buttons()
  , selectedButton(0)
  , dir(dir)
{
  setUIVisible(true);
}

Ogre::Overlay *UIOverlay::getOverlay(void) const {
  return overlay.get();
}

Ogre::Vector2 UIOverlay::pixelsToRelative(Ogre::Vector2 pixels) {
  return Ogre::Vector2(pixels.x / (Ogre::Real)Game::WIDTH, pixels.y / (Ogre::Real)Game::HEIGHT);
}

Ogre::Vector2 UIOverlay::relativeToPixels(Ogre::Vector2 relative) {
  return Ogre::Vector2(relative.x * (Ogre::Real)Game::WIDTH, relative.y * (Ogre::Real)Game::HEIGHT);
}

void UIOverlay::mousePressed(Ogre::Real x, Ogre::Real y)
{
  if (overlay->isVisible())
  {
    for (auto &&button : buttons) {
      Ogre::PanelOverlayElement *menuButton(button->getPanel());
      Ogre::Vector2 buttonSize(UIOverlay::relativeToPixels({ menuButton->getWidth(),
			      menuButton->getHeight() }));
      Ogre::Vector2 buttonPos(UIOverlay::relativeToPixels({ menuButton->getLeft(),
			      menuButton->getTop() }));
      if (x >= buttonPos.x && x <= buttonPos.x + buttonSize.x
	&& y >= buttonPos.y && y <= buttonPos.y + buttonSize.y) {
	button->getCallback()();
      }
    }
  }
}

void UIOverlay::mouseMoved(Ogre::Real x, Ogre::Real y) {
  if (overlay->isVisible())
  {
    for (auto &&button : buttons) {
      Ogre::PanelOverlayElement *menuButton(button->getPanel());
      Ogre::Vector2 buttonSize(UIOverlay::relativeToPixels({ menuButton->getWidth(),
			      menuButton->getHeight() }));
      Ogre::Vector2 buttonPos(UIOverlay::relativeToPixels({ menuButton->getLeft(),
			      menuButton->getTop() }));
      button->setHovered(
	x >= buttonPos.x
	&& x <= buttonPos.x + buttonSize.x
	&& y >= buttonPos.y
	&& y <= buttonPos.y + buttonSize.y
      );
    }
  }
  if (buttons.size()) {
    buttons[selectedButton]->setHovered(true);
  }
}

void UIOverlay::resetUICallbacks(void) {
  Joystick::registerGlobalCallback(joystickState::JS_A, [this](bool b, size_t) {
    if (!b && buttons.size()) {
      buttons[selectedButton]->getCallback()();
    }
  });
  Joystick::registerGlobalCallback(dir == Direction::VERTICAL ? joystickState::JS_LDOWN : joystickState::JS_LLEFT, [this](bool , size_t) {
    setSelectedButton(selectedButton + 1);
  });
  Joystick::registerGlobalCallback(dir == Direction::VERTICAL ? joystickState::JS_LUP : joystickState::JS_LRIGHT, [this](bool , size_t) {
    setSelectedButton(selectedButton - 1);
  }); 
  Mouse::getMouse().registerMouseMoveCallback([this](Ogre::Real x, Ogre::Real y) {
    mouseMoved(x, y);
  });
  Mouse::getMouse().registerCallback(OIS::MouseButtonID::MB_Left, [this](OIS::MouseEvent const &e) {
    mousePressed(
      static_cast<Ogre::Real>(e.state.X.abs),
      static_cast<Ogre::Real>(e.state.Y.abs)
    );
  });
}

bool UIOverlay::isVisible(void) const {
  return (getOverlay()->isVisible());
}

void UIOverlay::setUIVisible(bool b) {
  if (b) {
    overlay->show();
    setSelectedButton(0);
    resetUICallbacks();
  }
  else {
    overlay->hide();
  }
}

void UIOverlay::setSelectedButton(int i) {
  if (buttons.size()) {
    if (i < 0)
      i = buttons.size() + i;
    i %= buttons.size();
    buttons[selectedButton]->setHovered(false);
    selectedButton = static_cast<size_t>(i);
    buttons[selectedButton]->setHovered(true);
  }
}

size_t UIOverlay::getSelectedButton(void) const {
  return (selectedButton);
}
