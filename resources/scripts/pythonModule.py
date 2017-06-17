#!/usr/bin/python3
import PyPlugin

class pythonModule():
    def moveEntityFromVec(self, entity, vec, speed):
        vecx = vec.x()
        vecy = vec.y()
        posx = entity.pos.x()
        posy = entity.pos.y()
        newpos = PyPlugin.Vect(vecx - posx, vecy - posy).normalized()
        entity.setInput(newpos.x() * speed, newpos.y() * speed);

    def chasePlayerAI(self, entity, evaluater):
        vec = evaluater.closestPlayer(entity.pos)
        self.moveEntityFromVec(entity, vec, 0.01)

    def fleePlayerAI(self, entity, evaluater):
        vec = evaluater.closestPlayer(entity.pos)
        dist = PyPlugin.Vect(vec.x() - entity.pos.x(), vec.y() - entity.pos.y()).length2()
        if (dist < 75):
            self.moveEntityFromVec(entity, vec, -0.015)
        else:
            entity.setInput(0.0, 0.0);

    def chaseEnemyAI(self, entity, evaluater):
        vec = evaluater.closestEnemy(entity.pos)
        self.moveEntityFromVec(entity, vec, 0.01)

    def fleeEnemyAI(self, entity, evaluater):
        vec = evaluater.closestEnemy(entity.pos)
        dist = PyPlugin.Vect(vec.x() - entity.pos.x(), vec.y() - entity.pos.y()).length2()
        if (dist < 75):
            self.moveEntityFromVec(entity, vec, -0.015)
        else:
            entity.setInput(0.0, 0.0);
