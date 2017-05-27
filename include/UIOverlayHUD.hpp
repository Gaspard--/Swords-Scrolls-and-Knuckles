#ifndef UIOVERLAYHUD_HPP
# define UIOVERLAYHUD_HPP

# include "UIOverlay.hpp"

class UIOverlayHUD : public UIOverlay {

	public:
		UIOverlayHUD() = default;
		UIOverlayHUD(UIOverlayHUD const &) = delete;
		UIOverlayHUD(UIOverlayHUD &&) = delete;
		UIOverlayHUD &operator=(UIOverlayHUD const &) = delete;
		UIOverlayHUD &operator=(UIOverlayHUD &&) = delete;
		virtual ~UIOverlayHUD(void) = default;
		
		virtual void init(void);

	private:
	protected:
};

#endif // !UIOVERLAYHUD_HPP
