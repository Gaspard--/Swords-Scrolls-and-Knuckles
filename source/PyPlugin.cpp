#include "PyBindInstance.hpp"

PYBIND11_PLUGIN(PyPlugin)
{
    py::module m("PyPlugin", "Plugin wich allow access to a cpp class in python");

    /*
    ** How to define a class template for python :
    py::class_<ClassName>(m, "ClassName")
        .def_readwrite("var1", &ClassName::var1) // Py can access and modify var1.
        .def_readonly ("var2", &ClassName::var2) // Py can only read var2's value.
        .def("method1", &ClassName::method1) // Py can call the method1.
        .def_readwrite("method2", &ClassName::method2) // Exposes the return value of method2.
        .def_readonly("method3", &ClassName::method3) // Equivalent to a const method.
    */

    return m.ptr();
}
