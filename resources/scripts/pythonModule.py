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

def moveEntityFromVec(entity, vec, speed):
    newpos = subVec(vec, entity.pos).normalized()
    entity.setInput(mulVec(newpos, speed))

def chaseVec(entity, vec, evaluater, speed):
    moveEntityFromVec(entity, vec, speed)

def fleeFromVec(entity, vec, evaluater, speed):
    moveEntityFromVec(entity, vec, -speed)

def stand(entity):
	entity.setInput(PyPlugin.Vect(0.0, 0.0))

def shootAtVec(entity, vec, evaluater, speedChase, speedFlee, minRange, maxRange):
    dist = subVec(vec, entity.pos).length2()
    direc = subVec(vec, entity.pos).normalized()
    if (dist < minRange):
        fleeFromVec(entity, vec, evaluater, speedFlee)
    elif (dist >= minRange and dist <= maxRange):
    	entity.setDir(direc)
    else:
        chaseVec(entity, vec, evaluater, speedChase)

def followRightWall(entity, evaluater, speed):
    vec = evaluater.followRightWall(entity.pos)
    moveEntityFromVec(entity, vec, speed)

class pythonModule():
    def __init__(self):
        self.heroSpeed = 0.03

    def chasePlayerAI(self, entity, evaluater):
        vec = evaluater.closestPlayer(entity.pos)
        chaseVec(entity, vec, evaluater, 0.01)

    def fleePlayerAI(self, entity, evaluater):
        vec = evaluater.closestPlayer(entity.pos)
        fleeFromVec(entity, vec, evaluater, 0.015)

    def chaseEnemyAI(self, entity, evaluater):
        vec = evaluater.closestEnemy(entity.pos)
        chaseVec(entity, vec, evaluater, 0.01)

    def fleeEnemyAI(self, entity, evaluater):
        vec = evaluater.closestEnemy(entity.pos)
        fleeFromVec(entity, vec, evaluater, 0.015)

    def standAI(self, entity, evaluater):
        stand(entity)

    def shootPlayerAI(self, entity, evaluater):
        vec = evaluater.closestPlayer(entity.pos)
        shootAtVec(entity, vec, evaluater, 0.02, 0.04, 60, 80)

    def shootEnemyAI(self, entity, evaluater):
        vec = evaluater.closestEnemy(entity.pos)
        shootAtVec(entity, vec, evaluater, 0.03, 0.03, 60, 80)

    def followRightWallAI(self, entity, evaluater):
        evaluater.attack = False
        followRightWall(entity, evaluater, 0.1)
