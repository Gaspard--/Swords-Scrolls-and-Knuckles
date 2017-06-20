#include "PyBindInstance.hpp"
#include "Controllable.hpp"
#include "PyEvaluate.hpp"

PyBindInstance::PyBindInstance()
{
  try
  {
    main = py::module::import("__main__");
    globals = main.attr("__dict__");
    py::object importedModule = this->import("pythonModule", PYTHONMODULE, globals);
    py::object importedModuleAttr = importedModule.attr("pythonModule");
    pythonModule = importedModuleAttr();
    execAI[AI::CHASEPLAYER] = &PyBindInstance::chasePlayerAI;
    execAI[AI::FLEEPLAYER] = &PyBindInstance::fleePlayerAI;
    execAI[AI::CHASEENEMY] = &PyBindInstance::chaseEnemyAI;
    execAI[AI::FLEEENEMY] = &PyBindInstance::fleeEnemyAI;
    execAI[AI::STAND] = &PyBindInstance::standAI;
    execAI[AI::SHOOTPLAYER] = &PyBindInstance::shootPlayerAI;
    execAI[AI::SHOOTENEMY] = &PyBindInstance::shootEnemyAI;
    execAI[AI::FOLLOWRIGHTWALL] = &PyBindInstance::followRightWallAI;
    execAI[AI::LEADERCONTACTAI] = &PyBindInstance::leaderContactAI;
    execAI[AI::LEADERDISTANCEAI] = &PyBindInstance::leaderDistanceAI;
    execAI[AI::COMPANIONCONTACTAI] = &PyBindInstance::companionContactAI;
    execAI[AI::COMPANIONDISTANCEAI] = &PyBindInstance::companionDistanceAI;
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

void PyBindInstance::standAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("standAI")(&ctr, pyEv);
}

void PyBindInstance::shootPlayerAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("shootPlayerAI")(&ctr, pyEv);
}

void PyBindInstance::shootEnemyAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("shootEnemyAI")(&ctr, pyEv);

void PyBindInstance::followRightWallAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("followRightWallAI")(&ctr, &pyEv);
}

void PyBindInstance::leaderContactAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("leaderContactAI")(&ctr, &pyEv);
}

void PyBindInstance::leaderDistanceAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("leaderDistanceAI")(&ctr, &pyEv);
}

void PyBindInstance::companionContactAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("companionContactAI")(&ctr, &pyEv);
}

void PyBindInstance::companionDistanceAI(Controllable &ctr, PyEvaluate &pyEv)
{
  pythonModule.attr("companionDistanceAI")(&ctr, &pyEv);
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
