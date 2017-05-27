#ifndef UIOVERLAYMENU_HPP
# define UIOVERLAYMENU_HPP

# include "UIOverlay.hpp"

class UIOverlayMenu : public UIOverlay {

	public:
		UIOverlayMenu() = default;
		UIOverlayMenu(UIOverlayMenu const &) = delete;
		UIOverlayMenu(UIOverlayMenu &&) = delete;
		UIOverlayMenu &operator=(UIOverlayMenu const &) = delete;
		UIOverlayMenu &operator=(UIOverlayMenu &&) = delete;
		virtual ~UIOverlayMenu(void) = default;
		
		virtual void init(void);

	private:
	protected:
};

#endif // !UIOVERLAYMENU_HPP
