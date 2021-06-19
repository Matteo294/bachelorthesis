import random 
import numpy as np

class TLS:

    def __init__(self, N, T):
        self.T = T 
        self.N = N
        self.states = [random.choice([1/2, -1/2]) for _ in range(self.N)]
        self.nplus = self.states.count(1/2)
    
    def temperature(self):
        self.T =  4/(self.countStates(nplus=self.nplus+4, logflag=True) - self.countStates(nplus=self.nplus-2, logflag=True))
    
    def energy(self):
        return - self.N/2 * (2 / np.tanh(1/self.T) - 1/np.tanh(1/2/self.T))
    
    def thermalize(self):
        for n in range(1000):
            i = random.randint(0, self.N - 1)
            old_states = [s for s in self.states]
            self.flip(i)
            if self.deltapM(self.nplus, old_states.count(1/2), self.T) < random.uniform(0, 1):
                self.flip(i)
    
    def systemEnergy(self, nplus=None):
        if nplus is None:
            nplus = self.nplus
        return (2*nplus - self.N) / 2
    
    def flip(self, idx):
        self.states[idx] = - self.states[idx]
        self.nplus = self.states.count(1/2)
    
    def pM(self, nplus=None, Z=1):
        if nplus is None:
            nplus = self.nplus
        E = self.systemEnergy(nplus)
        return np.exp(-E/self.T)
    
    def deltapM(self, nplus1, nplus2, Z=1):
        E1 = self.systemEnergy(nplus1)
        E2 = self.systemEnergy(nplus2)
        deltaE = E2 - E1
        return np.exp(deltaE/self.T)
    
    def countStates(self, nplus=None, logflag=False):
        if nplus is None:
            nplus = self.nplus 
        if nplus > 3:
            arg = self.N*(np.log(self.N) - 1) - nplus*(np.log(nplus) - 1) - (self.N-nplus)*(np.log(self.N-nplus) - 1)
        else:
            arg = self.N*(np.log(self.N) - 1) - np.log(self.factorial(nplus)) - (self.N-nplus)*(np.log(self.N-nplus) - 1)

        if logflag is True:
            return arg 
        else:
            return np.exp(arg)
    
    def factorial(self, n):
        if n == 0:
            return 1
        else:
            return n * self.factorial(n - 1)