#ifndef SCENESTART_HPP
# define SCENESTART_HPP

# include "Renderer.hpp"
# include "Scene.hpp"
# include "UIOverlayStart.hpp"
# include "SceneMainMenu.hpp"

class SceneStart : public Scene
{
private:
  UIOverlayStart uiMenu;

public:
  SceneStart(Renderer &);
  virtual ~SceneStart(void) = default;

  virtual bool update(Game &, Ogre::FrameEvent const &) override;
  virtual void resetSceneCallbacks(Renderer &);
};

#endif // !SCENESTART_HPP
