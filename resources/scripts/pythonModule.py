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
        evaluater.attack = False
        vec = evaluater.closestPlayer(entity.pos)
        chaseVec(entity, vec, evaluater, 0.01)

    def fleePlayerAI(self, entity, evaluater):
        evaluater.attack = False
        vec = evaluater.closestPlayer(entity.pos)
        fleeFromVec(entity, vec, evaluater, 0.015)

    def chaseEnemyAI(self, entity, evaluater):
        evaluater.attack = False
        vec = evaluater.closestEnemy(entity.pos)
        chaseVec(entity, vec, evaluater, 0.01)

    def fleeEnemyAI(self, entity, evaluater):
        evaluater.attack = False
        vec = evaluater.closestEnemy(entity.pos)
        fleeFromVec(entity, vec, evaluater, 0.015)

    def standAI(self, entity, evaluater):
        evaluater.attack = False
        stand(entity)

    def shootPlayerAI(self, entity, evaluater):
        evaluater.attack = False
        vec = evaluater.closestPlayer(entity.pos)
        shootAtVec(entity, vec, evaluater, 0.02, 0.04, 60, 80)

    def shootEnemyAI(self, entity, evaluater):
        evaluater.attack = False
        vec = evaluater.closestEnemy(entity.pos)
        shootAtVec(entity, vec, evaluater, self.heroSpeed, self.heroSpeed, 30, 60)

    def followRightWallAI(self, entity, evaluater):
        evaluater.attack = False
        followRightWall(entity, evaluater, 0.1)

    def leaderContactAI(self, entity, evaluater):
        evaluater.attack = False
        vec = evaluater.closestEnemy(entity.pos)
        if (vec.equals(entity.pos)):
            followRightWall(entity, evaluater, self.heroSpeed)
        else:
            chaseVec(entity, vec, evaluater, self.heroSpeed)
            evaluater.attack = True

    def leaderDistanceAI(self, entity, evaluater):
        evaluater.attack = False
        vec = evaluater.closestEnemy(entity.pos)
        if (vec.equals(entity.pos)):
            followRightWall(entity, evaluater, self.heroSpeed)
        else:
            shootAtVec(entity, vec, evaluater, self.heroSpeed, self.heroSpeed, 30, 60)
            evaluater.attack = True

    def companionContactAI(self, entity, evaluater):
        evaluater.attack = False
        leader = evaluater.furtherPlayer(entity.pos)
        enemy = evaluater.closestEnemy(entity.pos)
        distLeader = subVec(entity.pos, leader)
        distEnemy = subVec(entity.pos, enemy)
        if (distEnemy.length2() > 1 and distEnemy.length2() < 100):
            chaseVec(entity, enemy, evaluater, self.heroSpeed)
            evaluater.attack = True
        elif (distLeader.length2() > 1 and distLeader.length2() < 100):
            chaseVec(entity, leader, evaluater, self.heroSpeed)
        else:
            followRightWall(entity, evaluater, self.heroSpeed)

    def companionDistanceAI(self, entity, evaluater):
        evaluater.attack = False
        leader = evaluater.furtherPlayer(entity.pos)
        enemy = evaluater.closestEnemy(entity.pos)
        distLeader = subVec(entity.pos, leader)
        distEnemy = subVec(entity.pos, enemy)
        if (distEnemy.length2() > 1 and distEnemy.length2() < 100):
            shootAtVec(entity, enemy, evaluater, self.heroSpeed, self.heroSpeed, 30, 60)
            evaluater.attack = True
        elif (distLeader.length2() > 1 and distLeader.length2() < 100):
            chaseVec(entity, leader, evaluater, self.heroSpeed)
        else:
            followRightWall(entity, evaluater, self.heroSpeed)
