from matplotlib.transforms import Transform
import numpy as np 
from matplotlib import pyplot as plt 
import random 

kB = 1
dE = 1
Nsamples = 100
Ncycles = 100000
Temp = 1

def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

def Energy(T, n=2):
    return - Nsamples * dE / 2 * (n / np.tanh(n*dE/2/kB/T) - 1/np.tanh(dE/2/kB/T))

def pM(nplus, T, Z=1):
    E = systemEnergy(nplus)
    return np.exp(-E/kB/T)

def deltapM(nplus1, nplus2, T, Z=1):
    E1 = systemEnergy(nplus1)
    E2 = systemEnergy(nplus2)
    deltaE = E2 - E1
    return np.exp(deltaE/kB/T)

def countStates(nplus, logflag=False): 
    if nplus > 3:
        arg = Nsamples*(np.log(Nsamples) - 1) - nplus*(np.log(nplus) - 1) - (Nsamples-nplus)*(np.log(Nsamples-nplus) - 1)
    else:
        arg = Nsamples*(np.log(Nsamples) - 1) - np.log(factorial(nplus)) - (Nsamples-nplus)*(np.log(Nsamples-nplus) - 1)

    if logflag is True:
        return arg 
    else:
        return np.exp(arg)

def systemEnergy(nplus):
    return (2*nplus - Nsamples) / 2

def systemEntropy(nplus):
    return kB*countStates(nplus, logflag=True)

def flip(s):
    return -s

avgE = []
Tvals =  np.linspace(-10, 10, 100)
betavals = [-1/x for x in Tvals]
for T in Tvals:
    states = [random.choice([-1/2, 1/2]) for _ in range(Nsamples)]
    _states = [s for s in states]
    energies = []
    entropies = []
    for n in range(Ncycles):
        i = random.randint(0, Nsamples - 1)
        _states[i] = flip(_states[i])
        nplus = states.count(1/2)
        _nplus = _states.count(1/2)
        r = random.uniform(0, 1)
        if deltapM(_nplus, nplus, T) > 1 or deltapM(_nplus, nplus, T) > r:
            states[i] = flip(states[i])
        else:
            _states[i] = flip(_states[i])
        if n >= 1000:
            energies.append(systemEnergy(nplus))
    avgE.append(sum(energies)/len(energies))

plt.plot(Tvals, Energy(Tvals))
plt.plot(Tvals, avgE)
plt.show()