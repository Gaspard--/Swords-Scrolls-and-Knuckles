#!/usr/bin/python3
import PyPlugin

class pythonModule():
    def chaseAI(self, entity, evaluater):
        speed = 0.01
        vec = evaluater.closestPlayer(entity.pos);
        vecx = vec.x()
        vecy = vec.y()
        posx = entity.pos.x()
        posy = entity.pos.y()
        newpos = PyPlugin.Vect(vecx - posx, vecy - posy).normalized()
        entity.setInput(newpos.x() * speed, newpos.y() * speed);
    pass
