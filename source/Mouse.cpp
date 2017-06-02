#include "Mouse.hpp"
#include "UIManager.hpp"

Mouse Mouse::mouseInstance;

Mouse &Mouse::getMouse(void) {

	return mouseInstance;
}

Mouse::Mouse(void)
	: Input<OIS::Mouse, OIS::MouseListener>()
{}

bool Mouse::mouseMoved(OIS::MouseEvent const &event) {

	(void)event;
	return true;
}

bool Mouse::mousePressed(OIS::MouseEvent const &event, OIS::MouseButtonID id) {

	std::clog << "Mouse::Mouse pressed." << std::endl;
	OIS::MouseState const &state = const_cast<OIS::MouseState const &>(event.state);
	if (id == OIS::MB_Left) {
		std::clog << state.X.abs << ":" << state.Y.abs << std::endl;
	}
	
	Ogre::OverlayManager::OverlayMapIterator it = Ogre::OverlayManager::getSingleton().getOverlayIterator();
	while (it.hasMoreElements()) {
		auto ov = it.getNext();
		if (ov->isVisible()) {
			UIManager::getByName(ov->getName())->mousePressed(state.X.abs, state.Y.abs);
		}
	}
	return true;
}

bool Mouse::mouseReleased(OIS::MouseEvent const &event, OIS::MouseButtonID id) {

	(void)event;
	(void)id;
	return true;
}
