#include "UIOverlay.hpp"

void UIOverlay::setOverlay(Ogre::Overlay *ov) {

	overlay = ov;
}

Ogre::Overlay *UIOverlay::getOverlay(void) const {

	return overlay;
}

Ogre::Vector2 UIOverlay::pixelsToRelative(Ogre::Vector2 pixels) {

	Ogre::Real x;
	Ogre::Real y;
	
	x = pixels.x / (Ogre::Real)Game::WIDTH;
	y = pixels.y / (Ogre::Real)Game::HEIGHT;
	return Ogre::Vector2(x, y);
}

Ogre::Vector2 UIOverlay::relativeToPixels(Ogre::Vector2 relative) {
	
	Ogre::Real x;
	Ogre::Real y;
	
	x = relative.x * (Ogre::Real)Game::WIDTH;
	y = relative.y * (Ogre::Real)Game::HEIGHT;
	return Ogre::Vector2(x, y);
}
