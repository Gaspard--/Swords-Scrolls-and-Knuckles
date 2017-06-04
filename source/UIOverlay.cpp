#include "UIOverlay.hpp"

void UIOverlay::setOverlay(Ogre::Overlay *ov) {

	overlay = ov;
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
