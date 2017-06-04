#include "Mouse.hpp"
#include "UIManager.hpp"

Mouse Mouse::mouseInstance;

Mouse &Mouse::getMouse(void) {

	return mouseInstance;
}

Mouse::Mouse(void)
	: Input<OIS::Mouse, OIS::MouseListener>()
{}

bool Mouse::mouseMoved(OIS::MouseEvent const &) {

	return true;
}

bool Mouse::mousePressed(OIS::MouseEvent const &event, OIS::MouseButtonID id) {

	OIS::MouseState const &state = const_cast<OIS::MouseState const &>(event.state);
	if (id == OIS::MB_Left) {
		Ogre::OverlayManager::OverlayMapIterator it(Ogre::OverlayManager::getSingleton().getOverlayIterator());
		while (it.hasMoreElements()) {
			auto ov = it.getNext();
			if (ov->isVisible()) {
				UIManager::getByName(ov->getName())->mousePressed(state.X.abs, state.Y.abs);
			}
		}
	}

	return true;
}

bool Mouse::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID) {

	return true;
}
