#ifndef SCENE_SELECTION_HPP
# define SCENE_SELECTION_HPP

# include "UIOverlaySelection.hpp"
# include "Scene.hpp"
# include "Renderer.hpp"

class SceneSelection : public Scene
{
private: 
  UIOverlaySelection uiSelection;

public:
  SceneSelection(Renderer &);
  virtual ~SceneSelection(void) = default;

  virtual bool update(Game &, Ogre::FrameEvent const &) override;
  virtual void resetSceneCallbacks(void);
};

#endif // !SCENE_SELECTION_HPP
