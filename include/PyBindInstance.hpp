#ifndef PYBINDINSTANCE_HPP_
# define PYBINDINSTANCE_HPP_

#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/eval.h>
#include <map>
#include <functional>

namespace py = pybind11;

class Controllable;
struct PyEvaluate;

#define PYTHONMODULE "resources/scripts/pythonModule.py"

namespace AI
{
  constexpr unsigned int CHASEPLAYER = 1u;
  constexpr unsigned int FLEEPLAYER = 2u;
  constexpr unsigned int CHASEENEMY = 3u;
  constexpr unsigned int FLEEENEMY = 4u;
  constexpr unsigned int STAND = 5u;
  constexpr unsigned int SHOOTPLAYER = 6u;
  constexpr unsigned int SHOOTENEMY = 7u;
  constexpr unsigned int FOLLOWRIGHTWALL = 8u;
  constexpr unsigned int LEADERCONTACTAI = 9u;
  constexpr unsigned int LEADERDISTANCEAI = 10u;
};

class	PyBindInstance
{
public:
    PyBindInstance();
    ~PyBindInstance() = default;

public:
    // Import a .py file.
    py::object import(const std::string &mod,
        const std::string &path, py::object &glb);
    void chasePlayerAI(Controllable &, PyEvaluate &);
    void fleePlayerAI(Controllable &, PyEvaluate &);
    void chaseEnemyAI(Controllable &, PyEvaluate &);
    void fleeEnemyAI(Controllable &, PyEvaluate &);
    void standAI(Controllable &, PyEvaluate &);
    void shootPlayerAI(Controllable &, PyEvaluate &);
    void shootEnemyAI(Controllable &, PyEvaluate &);
    void followRightWallAI(Controllable &, PyEvaluate &);
    void leaderContactAI(Controllable &, PyEvaluate &);
    void leaderDistanceAI(Controllable &, PyEvaluate &);
    std::map<unsigned int, std::function<void(PyBindInstance *, Controllable &, PyEvaluate &)>> execAI;

private:
    py::object main;
    py::object globals;
    py::object pythonModule;
};

#endif // !PYBINDINSTANCE_HPP_
