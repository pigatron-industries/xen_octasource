from simulator import *

sign = lambda x: math.copysign(1, x)

class TinkerbellMap(DiscreteSystem):
    def __init__(self, pos:Vector, a=0.9, b=-0.6013, c=2.0, d=0.5):
        super().__init__(pos)
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def system(self):
        x = self.pos[X]**2 - self.pos[Y]**2 + self.a*self.pos[X] + self.b*self.pos[Y]
        y = 2*self.pos[X]*self.pos[Y] + self.c*self.pos[X] + self.d*self.pos[Y]
        return Vector([x, y])
    

class HopalongAttractor(DiscreteSystem):
    def __init__(self, pos:Vector, a=0.4, b=1.0, c=0.0):
        super().__init__(pos)
        self.a = a
        self.b = b
        self.c = c

    def system(self):
        x = self.pos[Y] - sign(self.pos[X]) * math.sqrt(abs(self.b*self.pos[X] - self.c))
        y = self.a - self.pos[X]
        return Vector([x, y])
    

# http://www.3d-meier.de/tut5/Seite26.html
class MetzAttractor(DiscreteSystem):
    def __init__(self, pos:Vector, a=4.15, b=10):
        super().__init__(pos)
        self.a = a
        self.b = b

    def system(self):
        x = self.a * self.pos[X] * math.exp((1-math.sqrt(1+self.pos[Y]))/self.b)
        y = self.a * self.pos[X] - x
        return Vector([x, y])