#ifndef INPUT_HPP
# define INPUT_HPP

# include <OISEvents.h>
# include <OISInputManager.h>

template<typename T, typename E>
class Input : public E
{
  T *oisObject;

  protected:
    Input(void)
      : oisObject(nullptr)
    {}

  public:
    Input(Input const &) = delete;
    Input(Input &&) = delete;
    virtual ~Input(void) = default;
    Input &operator=(Input const &) = delete;
    Input &operator=(Input &&) = delete;

    void init(OIS::Type t, OIS::InputManager *im)
    {
      oisObject = static_cast<T *>(im->createInputObject(t, true));
      oisObject->setEventCallback(this);
    }

    void destroy(OIS::InputManager *im)
    {
      im->destroyInputObject(oisObject);
      oisObject = nullptr;
    }


    T *operator->(void) {
      return (oisObject);
    }
};

#endif // !INPUT_HPP
