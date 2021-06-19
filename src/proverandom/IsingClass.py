import random
import numpy as np

class IsingCanonical:

    # mu = 1
    def __init__(self, N, T, J=1, H=1):
        self.T = T
        self.N = N
        self.J = J
        self.H = H
        self.states = [random.choice([1/2, -1/2]) for _ in range(self.N)]
        self.nplus = self.states.count(1/2)
    
    def Hamiltonian(self):
        s1 = sum(self.states)*self.H
        s2 = 0
        for i in range(self.N - 1):
            s2 += self.states[i] * self.states[i+1]
        return -self.J * s2 + s1

    def flip(self, idx):
        self.states[idx] = - self.states[idx]
        if self.states[idx] > 0:
            self.nplus += 1
        else:
            self.nplus -= 1
        
    def thermalize(self, nsteps=1000):
        energy_old = self.Hamiltonian()
        for _ in range(nsteps):
            idx = random.randint(0, self.N - 1)
            self.flip(idx)
            energy_new = self.Hamiltonian()
            if energy_new > energy_old or np.exp((energy_old - energy_new)/self.T) > random.uniform(0, 1):
                energy_old = energy_new
            else:
                self.flip(idx)