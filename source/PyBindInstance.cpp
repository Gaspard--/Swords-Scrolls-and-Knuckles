#include "PyBindInstance.hpp"
#include "PyEvaluate.hpp"

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
    execAI[1u] = &PyBindInstance::chasePlayerAI;
    execAI[2u] = &PyBindInstance::fleePlayerAI;
    execAI[3u] = &PyBindInstance::chaseEnemyAI;
    execAI[4u] = &PyBindInstance::fleeEnemyAI;
  }
  catch (py::error_already_set const &e)
  {
    std::cerr << e.what() << std::endl;
    PyErr_Print();
  }
}

void PyBindInstance::chasePlayerAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("chasePlayerAI")(&ctr, pyEv);
}

void PyBindInstance::fleePlayerAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("fleePlayerAI")(&ctr, pyEv);
}

void PyBindInstance::chaseEnemyAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("chaseEnemyAI")(&ctr, pyEv);
}

void PyBindInstance::fleeEnemyAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("fleeEnemyAI")(&ctr, pyEv);
}

py::object    PyBindInstance::import(const std::string &mod, const std::string &path, py::object &glb)
{
  py::dict lcl;
  lcl["path"]        = py::cast(path);
  lcl["module_name"] = py::cast(mod);

  py::eval<py::eval_statements>(
    "import imp\n"
    "new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n",
    glb,
    lcl);
  return (lcl["new_module"]);
}
