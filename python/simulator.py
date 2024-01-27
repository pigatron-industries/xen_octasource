from typing import List
import math
import matplotlib.pyplot as plt
import numpy as np

X = 0
Y = 1
Z = 2


class Vector:
    def __init__(self, values:List[float]):
        self.values = values

    def __len__(self):
        return len(self.values)

    def __getitem__(self, key):
        return self.values[key]

    def __setitem__(self, key, value):
        self.values[key] = value



class System:
    def __init__(self, pos:Vector):
        self.pos = pos

    def update(self):
        raise NotImplementedError()

    def system(self) -> Vector:
        raise NotImplementedError()



class DiscreteSystem(System):
    def __init__(self, pos:Vector):
        self.pos = pos

    def update(self):
        self.pos = self.system()



class ContinuousSystem(System):
    def __init__(self, pos:Vector, dt:float=0.005):
        self.pos = pos
        self.dt = dt
        self.t = 0

    def update(self):
        self.t += self.dt
        delta = self.system()
        newpos = Vector([0 for _ in range(len(self.pos))])
        for i in range(len(self.pos)):
            newpos[i] = self.pos[i] + delta[i] * self.dt
        self.pos = newpos
        


class SystemSimulator():
    def __init__(self, system:System):
        self.system = system
        self.path:List[Vector] = []

    def simulate(self, steps=1000):
        for i in range(steps):
            self.system.update()
            self.path.append(self.system.pos)

    def plot1D(self, axis=X):
        plt.plot([pos[axis] for pos in self.path])
        plt.show()

    def plot2D(self, axis=(X, Y)):
        plt.scatter([pos[axis[0]] for pos in self.path], [pos[axis[1]] for pos in self.path], s=1)
        # plt.gca().set_aspect('equal', adjustable='box')
        plt.show()

    def plotIsometric(self, angle1=45, angle2=-35):
        plotpath = []
        angle1_rad = math.radians(angle1)
        angle2_rad = math.radians(angle2)

        for pos in self.path:
            output = [pos[X], pos[Y], pos[Z]]

            # input = Vector([output[X], output[Y], output[Z]])
            # output[X] = np.cos(angle1_rad)*input[X] - np.sin(angle1_rad)*input[Y]
            # output[Y] = np.sin(angle1_rad)*input[X] + np.cos(angle1_rad)*input[Y]
            # output[Z] = input[Z]

            # input = Vector([output[X], output[Y], output[Z]])
            # output[X] = input[X]
            # output[Y] = np.cos(angle1_rad)*input[Y] - np.sin(angle1_rad)*input[Z]
            # output[Z] = np.sin(angle1_rad)*input[Y] + np.cos(angle1_rad)*input[Z]

            input = Vector([output[X], output[Y], output[Z]])
            x = np.cos(angle1_rad)*input[X] - np.sin(angle1_rad)*input[Y]
            y = np.sin(angle2_rad)*np.sin(angle1_rad)*input[X] + np.sin(angle2_rad)*np.cos(angle1_rad)*input[Y] + np.cos(angle2_rad)*input[Z]
            
            plotpath.append(Vector([x, y]))
        plt.scatter([pos[X] for pos in plotpath], [pos[Y] for pos in plotpath], s=1)
        # plt.gca().set_aspect('equal', adjustable='box')
        plt.show()
        
