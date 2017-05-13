#ifndef SCENE_HPP
# define SCENE_HPP

class Game;
class Renderer;

class Scene
{
  protected:
    Renderer &_renderer;

  public:
    Scene(void);
    Scene(Scene const &) = delete;
    Scene(Scene &&) = delete;
    Scene &operator=(Scene const &) = delete;
    Scene &operator=(Scene &&) = delete;
    virtual ~Scene(void) = default;

    /// Used to load all the elements of the new scene
    virtual void load(void);

    /// Used to close personnal resources. Do *NOT* free Ogre's scene elements
    /// (entities, lights etc.).
    virtual void unload(void);
};

#endif // !SCENE_HPP
