#ifndef SCENE_SCOREBOARD_HPP
# define SCENE_SCOREBOARD_HPP

# include "UIOverlayScoreboard.hpp"
# include "Scene.hpp"

class SceneScoreboard : public Scene
{
private:
  UIOverlayScoreboard uiScoreboard;

public:
  SceneScoreboard(Renderer &);
  virtual ~SceneScoreboard(void) = default;

  virtual void resetSceneCallbacks(Renderer &);
};

#endif // !SCENE_SCOREBOARD_HPP
