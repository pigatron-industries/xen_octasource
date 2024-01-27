from simulator import *
import math


class CliffordAttractor(DiscreteSystem):
    def __init__(self, pos:Vector, a=-1.7, b=1.3, c=-0.1, d=-1.21):
        super().__init__(pos)
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def system(self):
        x = math.sin(self.a*self.pos[Y]) + self.c * math.cos(self.a*self.pos[X])
        y = math.sin(self.b*self.pos[X]) + self.d * math.cos(self.b*self.pos[Y])
        return Vector([x, y])
    

class AizawaAttractor(ContinuousSystem):
    def __init__(self, pos:Vector, a=0.95, b=0.7, c=0.6, d=3.5, e=0.25, f=0.1):
        super().__init__(pos)
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.e = e
        self.f = f

    def system(self):
        dx = (self.pos[Z] - self.b) * self.pos[X] - self.d * self.pos[Y]
        dy = self.d * self.pos[X] + (self.pos[Z] - self.b) * self.pos[Y]
        dz = self.c + self.a * self.pos[Z] - (self.pos[Z]**3) / 3 - (self.pos[X]**2 + self.pos[Y]**2) * (1 + self.e * self.pos[Z]) + self.f * self.pos[Z] * (self.pos[X]**3)        
        return Vector([dx, dy, dz])
    

class DadrasAttractor(ContinuousSystem):
    def __init__(self, pos:Vector, p = 3, q = 2.7, r = 1.7, s = 2.0, e = 9.0):
        super().__init__(pos)
        self.p = p
        self.q = q
        self.r = r
        self.s = s
        self.e = e

    def system(self):
        dx = self.pos[Y] - self.p * self.pos[X] + self.q * self.pos[Y] * self.pos[Z]
        dy = self.r * self.pos[Y] - self.pos[X] * self.pos[Z] + self.pos[Z]
        dz = self.s * self.pos[X] * self.pos[Y] - self.e * self.pos[Z]
        return Vector([dx, dy, dz])
    

class ThomasAttractor(ContinuousSystem):
    def __init__(self, pos:Vector, b=0.19):
        super().__init__(pos)
        self.b = b

    def system(self):
        dx = math.sin(self.pos[Y]) - self.b * self.pos[X]
        dy = math.sin(self.pos[Z]) - self.b * self.pos[Y]
        dz = math.sin(self.pos[X]) - self.b * self.pos[Z]
        return Vector([dx, dy, dz])
    

class HalvorsenAttractor(ContinuousSystem):
    def __init__(self, pos:Vector, a = 1.4):
        super().__init__(pos, dt=0.005)
        self.a = a

    def system(self):
        dx = -self.a * self.pos[X] - 4 * self.pos[Y] - 4 * self.pos[Z] - self.pos[Y]**2
        dy = -self.a * self.pos[Y] - 4 * self.pos[Z] - 4 * self.pos[X] - self.pos[Z]**2
        dz = -self.a * self.pos[Z] - 4 * self.pos[X] - 4 * self.pos[Y] - self.pos[X]**2
        return Vector([dx, dy, dz])
    

class NoseHooverAttractor(ContinuousSystem):
    def __init__(self, pos:Vector, a = 1.5):
        super().__init__(pos)
        self.a = a

    def system(self):
        dx = self.pos[Y]
        dy = self.pos[Z]*self.pos[Y] - self.pos[X]
        dz = self.a - self.pos[Y]**2
        return Vector([dx, dy, dz])
    

class HadleyAttractor(ContinuousSystem):
    def __init__(self, pos:Vector, a = 0.2, b = 4.0, c = 8.0, d = 1.0):
        super().__init__(pos)
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def system(self):
        dx = -self.pos[Y]**2 - self.pos[Z]**2 - self.a * self.pos[X] + self.a * self.c
        dy = self.pos[X] * self.pos[Y] - self.b * self.pos[X] * self.pos[Z] - self.pos[Y] + self.d
        dz = self.b * self.pos[X] * self.pos[Y] + self.pos[X] * self.pos[Z] - self.pos[Z]
        return Vector([dx, dy, dz])
    

class LorenzMod1Attractor(ContinuousSystem):
    def __init__(self, pos:Vector, a = 0.1, b = 4.0, c = 14.0, d = 0.08):
        super().__init__(pos, dt=0.001)
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def system(self):
        dx = -self.a * self.pos[X] + self.pos[Y] * self.pos[Y] - self.pos[Z] * self.pos[Z] + self.a * self.c
        dy = self.pos[X] * (self.pos[Y] - self.b * self.pos[Z]) + self.d
        dz = self.pos[Z] + self.pos[X] * (self.b * self.pos[Y] + self.pos[Z])
        return Vector([dx, dy, dz])
    

class LorenzMod2Attractor(ContinuousSystem):
    def __init__(self, pos:Vector, a = 0.9, b = 5.0, c = 9.9, d = 1.0):
        super().__init__(pos)
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def system(self):
        dx = -self.a * self.pos[X] + self.pos[Y] * self.pos[Y] - self.pos[Z] * self.pos[Z] + self.a * self.c
        dy = self.pos[X] * (self.pos[Y] - self.b * self.pos[Z]) + self.d
        dz = -self.pos[Z] + self.pos[X] * (self.b * self.pos[Y] + self.pos[Z])
        return Vector([dx, dy, dz])