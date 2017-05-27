#ifndef UIOVERLAY_HPP
# define UIOVERLAY_HPP

# include <Overlay/OgreOverlay.h>

class UIOverlay {

	public:
		UIOverlay() = default;
		UIOverlay(UIOverlay const &) = delete;
		UIOverlay(UIOverlay &&) = delete;
		UIOverlay &operator=(UIOverlay const &) = delete;
		UIOverlay &operator=(UIOverlay &&) = delete;
		virtual ~UIOverlay(void) = default;
		
		void setOverlay(Ogre::Overlay *);
		virtual void init(void) = 0;

	private:
	protected:
		Ogre::Overlay *overlay;
};

#endif // !UIOVERLAY_HPP
