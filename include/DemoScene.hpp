#ifndef DEMO_SCENE_HPP
# define DEMO_SCENE_HPP

# include <memory>
# include <OgreEntity.h>
# include <OgreLight.h>
# include <OgreSceneNode.h>
# include "Scene.hpp"

class Game;

class DemoScene : public Scene
{
  public:
    DemoScene(void) = delete;
    DemoScene(Game &);
    DemoScene(DemoScene const &) = delete;
    DemoScene(DemoScene &&) = delete;
    virtual ~DemoScene(void) = default;
    DemoScene operator=(DemoScene const &) = delete;
    DemoScene operator=(DemoScene &&) = delete;

    virtual void load(void);
};

#endif // !DEMO_SCENE_HPP
