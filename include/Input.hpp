#ifndef INPUT_HPP
# define INPUT_HPP

# include <OISEvents.h>
# include <OISInputManager.h>

template<typename T>
class Input : public OIS::KeyListener
{
  T *oisobject;

  protected:
    Input(void)
      : oisobject(nullptr)
    {}

  public:
    Input(Input const &) = delete;
    Input(Input &&) = delete;
    virtual ~Input(void) = default;
    Input &operator=(Input const &) = delete;
    Input &operator=(Input &&) = delete;

    void init(OIS::Type t, OIS::InputManager *im)
    {
      oisobject =static_cast<T *>(im->createInputObject(t, true));
      oisobject->setEventCallback(this);
    }

    void destroy(OIS::InputManager *im)
    {
      im->destroyInputObject(oisobject);
      oisobject = nullptr;
    }


    T *operator->(void) {
      return (oisobject);
    }
};

#endif // !INPUT_HPP
