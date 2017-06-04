#ifndef MOUSE_HPP
# define MOUSE_HPP

# include <iostream>
# include <OISMouse.h>
# include <Overlay/OgreOverlay.h>
# include <Overlay/OgreOverlayManager.h>
# include "Input.hpp"

class Mouse : public Input<OIS::Mouse, OIS::MouseListener> {

	public:
		Mouse(Mouse const &) = delete;
		Mouse(Mouse &&) = delete;
		virtual ~Mouse(void) = default;
		Mouse &operator=(Mouse const &) = delete;
		Mouse &operator=(Mouse &&) = delete;

		static Mouse &getMouse(void);

	protected:
		virtual bool mouseMoved(OIS::MouseEvent const &);
		virtual bool mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID);
		virtual bool mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID);

	private:
		static Mouse mouseInstance;
		Mouse(void);
};

#endif // !MOUSE_HPP
