#ifndef SCENE_MAIN_MENU_HPP
# define SCENE_MAIN_MENU_HPP

# include "UIOverlayMenu.hpp"
# include "Scene.hpp"
# include "Renderer.hpp"

/**
 * Class representation of the ingame scene.
 * This class should handle most basic interactions between game logic
 * and entities.
 * Should NOT be inherited. (ideally)
 */
class SceneMainMenu : public Scene
{
private:
  UIOverlayMenu uiMenu;

public:
  SceneMainMenu(Renderer &);
  virtual ~SceneMainMenu(void) = default;

  virtual bool update(Game &, Ogre::FrameEvent const &) override;
  virtual void resetSceneCallbacks(void);
};

#endif // !SCENE_MAIN_MENU_HPP
