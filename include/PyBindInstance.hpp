#ifndef PYBINDINSTANCE_HPP_
# define PYBINDINSTANCE_HPP_

#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/eval.h>
#include <map>

namespace py = pybind11;

class Controllable;
class PyEvaluate;

#define PYTHONMODULE "resources/scripts/pythonModule.py"

class	PyBindInstance
{
public:
    PyBindInstance();
    ~PyBindInstance() = default;

public:
    // Import a .py file.
    py::object import(const std::string &mod,
        const std::string &path, py::object &glb);
    void chaseAI(Controllable &, PyEvaluate &);

private:
    py::object main;
    py::object globals;
    py::object pythonModule;
};

#endif // !PYBINDINSTANCE_HPP_
