#ifndef DEMO_SCENE_HPP
# define DEMO_SCENE_HPP

# include <memory>
# include <OgreEntity.h>
# include <OgreLight.h>
# include <OgreSceneNode.h>
# include "Scene.hpp"
# include "Entity.hpp"

class Game;

class DemoScene : public Scene
{
  public:
    DemoScene(void);
    DemoScene(DemoScene const &) = delete;
    DemoScene(DemoScene &&) = delete;
    virtual ~DemoScene(void) = default;
    DemoScene operator=(DemoScene const &) = delete;
    DemoScene operator=(DemoScene &&) = delete;

    virtual void load(void);
    virtual bool update(void);

  private:
    Ogre::SceneNode *cameraNode;
    Ogre::Light *light;

    Entity ogre;
    Entity ground;
};

#endif // !DEMO_SCENE_HPP
