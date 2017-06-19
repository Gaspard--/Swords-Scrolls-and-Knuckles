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
# include <Overlay/OgreFontManager.h>
# include <OISInputManager.h>

# include "Renderer.hpp"
# include "Keyboard.hpp"
# include "Mouse.hpp"
# include "Music.hpp"

class Game : public Ogre::WindowEventListener, public Ogre::FrameListener
{
    /// Ogre config plugins & resource path
    static constexpr char const *PLUGINS_CONFIG_PATH = "resources/cfg/plugins.cfg";
    static constexpr char const *RESOURCES_CONFIG_PATH = "resources/cfg/resources.cfg";

    /// Root Ogre instance.
    Ogre::Root root;
    Ogre::RenderWindow *window;
    OIS::InputManager *inputManager;
    std::unique_ptr<Renderer> renderer;

    /// Setup functions (called by Keyboard::setup())
    void setupResources(void);
    void setupRenderSystem(void);
    void setupOIS(void);

    /// Instanciate a Joystick, return true if successful.
    bool addJoystick(size_t);

  protected:
    /// Ogre::FrameListener
    virtual bool frameRenderingQueued(Ogre::FrameEvent const &evt) override;

    // Ogre::WindowEventListener
    virtual void windowClosed(Ogre::RenderWindow* rw) override;

  public:
    Game();
    Game(Game const &) = delete;
    Game(Game &&) = delete;
    Game &operator=(Game const &) = delete;
    Game &operator=(Game &&) = delete;
    ~Game(void);

	// Size of window
	static constexpr int const HEIGHT = 1080;
	static constexpr int const WIDTH = 1920;

    /// Run the game
    void run(void);

    Music music;

    /// Return the root instance
    Ogre::Root &getRoot(void);
    Ogre::Root const &getRoot(void) const;

    /// Return the window instance
    Ogre::RenderWindow &getWindow(void);
    Ogre::RenderWindow const &getWindow(void) const;

    /// Return the renderer instance
    Renderer &getRenderer(void);
    Renderer const &getRenderer(void) const;

    class SetupException : public std::runtime_error {
      public:
	using std::runtime_error::runtime_error;
	using std::runtime_error::what;
    };

    struct GameQuitException {};
};
#endif // !GAME_HPP
