#ifndef PYBINDINSTANCE_HPP_
# define PYBINDINSTANCE_HPP_

#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/eval.h>
#include <map>

namespace py = pybind11;

class	PyBindInstance
{
public:
    PyBindInstance();
    ~PyBindInstance() = default;

public:
    // Import a .py file.
    py::object import(const std::string &mod,
        const std::string &path, py::object &glb);
    void executeAI();

private:
    py::object main;
    // Put this on every mob :
    // py::object globals;

    // The std::string may be replaced to match the type of monster's type id.
    // EDIT: if we do only make one class, a map will not be necessary.
    std::map<std::string, py::object> modules;
    std::map<std::string, py::object> wrappers;
};

#endif // !PYBINDINSTANCE_HPP_
