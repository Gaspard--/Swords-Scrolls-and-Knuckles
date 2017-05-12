#ifndef GAME_HPP
# define GAME_HPP

# include <memory>
# include <OgreRoot.h>
# include <OgreRenderWindow.h>
# include <OgreConfigFile.h>
# include <OgreResourceGroupManager.h>
# include <OgreTextureManager.h>
# include <OgreException.h>
# include <OgreWindowEventUtilities.h>

# include "Renderer.hpp"

class Game
{
  private:
    /// Root Ogre instance.
    Ogre::Root _root;
    std::unique_ptr<Renderer> _renderer;
    std::unique_ptr<Ogre::RenderWindow> _window;

    void setupResources(void);
    void setupRenderSystem(void);

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

    /// Return the root instance
    Ogre::Root &getRoot(void);
    Ogre::Root const &getRoot(void) const;

    /// Return the window instance
    Ogre::RenderWindow &getWindow(void);
    Ogre::RenderWindow const &getWindow(void) const;

    /// Return the renderer instance
    Renderer &getRenderer(void);
    Renderer const &getRenderer(void) const;

    /// Set the current scene to the selected one.
    void setCurrentScene(Scene *);

    class SetupException : public std::runtime_error {
      public:
	using std::runtime_error::runtime_error;
	using std::runtime_error::what;
    };
};
#endif // !GAME_HPP
