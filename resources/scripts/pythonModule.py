#!/usr/bin/python3
import PyPlugin

def addVec(a, b):
    ax = a.x()
    ay = a.y()
    bx = b.x()
    by = b.y()
    return (PyPlugin.Vect(ax + bx, ay + by))

def subVec(a, b):
    ax = a.x()
    ay = a.y()
    bx = b.x()
    by = b.y()
    return (PyPlugin.Vect(ax - bx, ay - by))

def mulVec(a, b):
    ax = a.x()
    ay = a.y()
    return (PyPlugin.Vect(ax * b, ay * b))

class pythonModule():
    def moveEntityFromVec(self, entity, vec, speed):
        newpos = subVec(vec, entity.pos).normalized()
        entity.setInput(mulVec(newpos, speed))

    def chasePlayerAI(self, entity, evaluater):
        vec = evaluater.closestPlayer(entity.pos)
        self.moveEntityFromVec(entity, vec, 0.01)

    def fleePlayerAI(self, entity, evaluater):
        vec = evaluater.closestPlayer(entity.pos)
        dist = PyPlugin.Vect(vec.x() - entity.pos.x(), vec.y() - entity.pos.y()).length2()
        if (dist < 75):
            self.moveEntityFromVec(entity, vec, -0.015)
        else:
            self.standAI(entity, evaluater)

    def chaseEnemyAI(self, entity, evaluater):
        vec = evaluater.closestEnemy(entity.pos)
        self.moveEntityFromVec(entity, vec, 0.01)

    def fleeEnemyAI(self, entity, evaluater):
        vec = evaluater.closestEnemy(entity.pos)
        dist = PyPlugin.Vect(vec.x() - entity.pos.x(), vec.y() - entity.pos.y()).length2()
        if (dist < 75):
            self.moveEntityFromVec(entity, vec, -0.015)
        else:
            self.standAI(entity, evaluater)

    def standAI(self, entity, evaluater):
        entity.setInput(PyPlugin.Vect(0.0, 0.0))
