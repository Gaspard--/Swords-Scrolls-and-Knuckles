#ifndef SCENEGAMEOVER_HPP
# define SCENEGAMEOVER_HPP

# include "Renderer.hpp"
# include "Scene.hpp"
# include "UIOverlayGO.hpp"
# include "SceneMainMenu.hpp"

class SceneGameOver : public Scene
{
private:
  UIOverlayGO uiMenu;

public:
  SceneGameOver(Renderer &);
  virtual ~SceneGameOver(void) = default;

  virtual void resetSceneCallbacks(Renderer &);
};

#endif // !SCENEGAMEOVER_HPP
