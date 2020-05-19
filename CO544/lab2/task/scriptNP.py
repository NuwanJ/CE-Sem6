
import numpy as np
import matplotlib.pyplot as plt

class RandomWalk :

    def __init__(self, position):
        self.position = position

    def stepsGenerator(self, stepCount):
        return np.random.randn(stepCount)

    def walk(self):
        start=self.position
        path=[]
        path=[start]
        stepCount = 500
        steps = self.stepsGenerator(stepCount)

        for s in steps:
            go = 1 if(s>0) else -1
            path.append(path[-1] + go)

        return path


random_walker = RandomWalk(200)
print(random_walker.walk())
