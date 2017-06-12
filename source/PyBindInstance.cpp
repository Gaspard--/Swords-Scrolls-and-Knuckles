#include "PyBindInstance.hpp"

PyBindInstance::PyBindInstance()
: main(py::module::import("__main__"))
{
    // Add an initialisation for every module/wrapper.

    // Put this on every mob :
    // this->globals = this->main.attr("__dict__");
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
