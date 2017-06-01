#ifndef DEMO_SCENE_HPP
# define DEMO_SCENE_HPP

# include <memory>
# include <OgreEntity.h>
# include <OgreLight.h>
# include <OgreSceneNode.h>
# include "Scene.hpp"
# include "AnimatedEntity.hpp"
# include "Entity.hpp"

class DemoScene : public Scene
{
private:
  Ogre::SceneNode *cameraNode;
  Ogre::Light *light;

  AnimatedEntity illidan;
  Entity ground;

public:
  DemoScene(Game &);

  DemoScene(DemoScene const &) = delete;
  DemoScene(DemoScene &&) = delete;
  virtual ~DemoScene(void) = default;
  DemoScene operator=(DemoScene const &) = delete;
  DemoScene operator=(DemoScene &&) = delete;

  virtual bool update(Game &, Ogre::FrameEvent const &) override;
};

#endif // !DEMO_SCENE_HPP
