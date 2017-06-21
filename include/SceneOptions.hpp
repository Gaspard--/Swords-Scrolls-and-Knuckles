#ifndef SCENE_OPTIONS_HPP
# define SCENE_OPTIONS_HPP

# include "UIOVerlayOptions.hpp"
# include "Scene.hpp"
# include "Renderer.hpp"

class SceneOptions : public Scene
{
private: 
  UIOverlayOptions uiOptions;

public:
  SceneOptions(Renderer &);
  virtual ~SceneOptions(void) = default;

  virtual void resetSceneCallbacks(Renderer &) override;
};

#endif // !SCENE_OPTIONS_HPP
