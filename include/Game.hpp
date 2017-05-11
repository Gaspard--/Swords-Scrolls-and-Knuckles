#ifndef GAME_HPP
# define GAME_HPP

# include <OgreRoot.h>
# include <OgreRenderWindow.h>
# include <OgreException.h>

class Game
{
  private:
    /// Root Ogre instance.
    Ogre::Root _root;
    std::unique_ptr<Ogre::RenderWindow> _window;

  public:
    Game(void);
    Game(Game const &) = delete;
    Game(Game &&) = delete;
    Game &operator=(Game const &) = delete;
    Game &operator=(Game &&) = delete;
    ~Game(void);

    static char const *const PLUGINS_CONFIG_PATH;
    static char const *const RESOURCES_CONFIG_PATH;

    /// Set up the game (load saves etc.)
    /// Throws SetupException in case of error.
    void setup(void);

    /// Run the game
    void run(void);

    class SetupException : public std::runtime_error {
      public:
	using std::runtime_error::runtime_error;
	using std::runtime_error::what;
    };
};
#endif // !GAME_HPP
