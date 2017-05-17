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
# include <OgreFrameListener.h>
# include <OISInputManager.h>

# include "Renderer.hpp"
# include "Keyboard.hpp"

class Game : public Ogre::WindowEventListener, public Ogre::FrameListener
{
    /// Singleton instance
    static Game gameInstance;

    /// Root Ogre instance.
    Ogre::Root root;
    Ogre::RenderWindow *window;
    OIS::InputManager *inputManager;
    std::unique_ptr<Renderer> renderer;

    /// Setup functions (called by Keyboard::setup())
    void setupResources(void);
    void setupRenderSystem(void);
    void setupOIS(void);

    /// Private constructor (Singleton)
    Game(void);

  protected:
    /// Ogre::FrameListener
    virtual bool frameRenderingQueued(Ogre::FrameEvent const &evt);

    // Ogre::WindowEventListener
    virtual void windowClosed(Ogre::RenderWindow* rw);

  public:
    Game(Game const &) = delete;
    Game(Game &&) = delete;
    Game &operator=(Game const &) = delete;
    Game &operator=(Game &&) = delete;
    ~Game(void);

    /// Ogre config plugins & resource path
    static constexpr char const *PLUGINS_CONFIG_PATH = "resources/cfg/plugins.cfg";
    static constexpr char const *RESOURCES_CONFIG_PATH = "resources/cfg/resources.cfg";

    /// Singleton getter
    static Game &getGame(void);

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
