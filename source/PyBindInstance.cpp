#include "PyBindInstance.hpp"
#include "Enemy.hpp"
#include "Vect.hpp"

namespace PyPlugin
{
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
        ;
    */

    py::class_<Vect<2u, double>>(m, "Vect")
      .def(py::init<double, double>())
      .def("x", &Vect<2u, double>::x)
      .def("y", &Vect<2u, double>::y)
      .def("normalized", &Vect<2u, double>::normalized)
      ;

    py::class_<Fixture, Controllable>(m, "Controllable")
      .def("setInput", &Controllable::setInputPy)
      .def_readwrite("pos", &Fixture::pos)
      ;

    py::class_<PyEvaluate>(m, "PyEvaluate")
      .def("closestPlayer", &PyEvaluate::closestPlayer)
      ;

    return m.ptr();
  }
}

PyBindInstance::PyBindInstance()
{
  try
  {
    Py_Initialize();
    PyPlugin::pybind11_init();

    main = py::module::import("__main__");
    globals = main.attr("__dict__");
    py::object importedModule = this->import("pythonModule", PYTHONMODULE, globals);
    py::object importedModuleAttr = importedModule.attr("pythonModule");
    pythonModule = importedModuleAttr();
  }
  catch (py::error_already_set const &e)
  {
    std::cerr << e.what() << std::endl;
    PyErr_Print();
  }
}
}

py::object    PyBindInstance::import(const std::string &mod, const std::string &path, py::object &glb)
{
    py::dict  lcl;
    lcl["path"]        = py::cast(path);
    lcl["module_name"] = py::cast(mod);

    py::eval<py::eval_statements>(
        "import imp\n"
        "new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n",
        glb,
        lcl);
    return lcl["new_module"];
}
