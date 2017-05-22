#ifndef DEMO_SCENE_HPP
# define DEMO_SCENE_HPP

# include <memory>
# include <OgreEntity.h>
# include <OgreLight.h>
# include <OgreSceneNode.h>
# include "Scene.hpp"
# include "Entity.hpp"

class DemoScene : public Scene
{
  private:
    Ogre::SceneNode *cameraNode;
    Ogre::Light *light;

    Entity ogre;
    Entity ground;

  public:
    constexpr DemoScene(void)
      : cameraNode(nullptr)
      , light(nullptr)
    {}

    DemoScene(DemoScene const &) = delete;
    DemoScene(DemoScene &&) = delete;
    virtual ~DemoScene(void) = default;
    DemoScene operator=(DemoScene const &) = delete;
    DemoScene operator=(DemoScene &&) = delete;

    virtual void load(Game &) override;
    virtual bool update(Game &) override;
};

#endif // !DEMO_SCENE_HPP
