#ifndef SCENE_HPP
# define SCENE_HPP

class Game;

class Scene
{
  public:
    constexpr Scene(void) = default;
    Scene(Scene const &) = delete;
    Scene(Scene &&) = delete;
    Scene &operator=(Scene const &) = delete;
    Scene &operator=(Scene &&) = delete;
    virtual ~Scene(void) = default;

    /// Used to load all the elements of the new scene
    virtual void load(Game &);

    /// Used to close personnal resources. Do *NOT* free Ogre's scene elements
    /// (entities, lights etc.).
    virtual void unload(Game &);

    /// Called each frame to update scene logic.
    /// Return value: false to exit the game, true otherwise.
    virtual bool update(Game &);
};

#endif // !SCENE_HPP
