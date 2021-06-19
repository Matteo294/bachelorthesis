import TLSclass as TLSS
import random
import numpy as np
from matplotlib import pyplot as plt

N1 = 100
N2 = 100
T1 = 10
T2 = 200
Ncycles = int(1e5)

S1 = TLSS.TLS(N1, T1)
S2 = TLSS.TLS(N2, T2)
Etot = S1.systemEnergy() + S2.systemEnergy()

S1.thermalize()
S2.thermalize() 


def totalEntropy(dn1=0, dn2=0, logflag=False):
    if logflag :
        return S1.countStates(S1.nplus+dn1, logflag=True) + S2.countStates(S2.nplus+dn2, logflag=True)
    else:
        return np.exp(S1.countStates(S1.nplus+dn1, logflag=True) + S2.countStates(S2.nplus+dn2, logflag=True))

def temp():
    x = (totalEntropy(1, 1) - totalEntropy(-1, -1)) / 4
    return 1/x

def getSpin(N1, N2, idx):

temperatures = []
entropies = []
ent1 = []
ent2 = []
TT1 = []
TT2 = []
for _ in range(Ncycles):
    oldState = [s for s in S2.states]
    oldEntropy = S1.countStates(logflag=True) + S2.countStates(logflag=True)
    idx1 = random.randint(0, N1 + N2 - 1)
    idx2 = random.randint(0, N1 + N2 - 1)
    S1.flip(idx1)
    S2.flip()

    if idx >= N1:
        S2.flip(idx - N1)
        entropy = S1.countStates(logflag=True) + S2.countStates(logflag=True)
        if np.exp((entropy - oldEntropy)) < random.uniform(0, 1):
            S2.flip(idx - N1)
        S1.temperature()
        S2.temperature()
        TT1.append(S1.T)
        TT2.append(S2.T)
        ent1.append(S1.countStates(logflag=True))
        ent2.append(S2.countStates(logflag=True))
    else:
        S1.flip(idx)
        entropy = S1.countStates(logflag=True) + S2.countStates(logflag=True)
        if np.exp((entropy - oldEntropy)) < random.uniform(0, 1):
            S1.flip(idx)
        S1.temperature()
        S2.temperature()
        TT1.append(S1.T)
        TT2.append(S2.T)
        ent1.append(S1.countStates(logflag=True))
        ent2.append(S2.countStates(logflag=True))
    entropies.append(S1.countStates(logflag=True) + S2.countStates(logflag=True))
    #print(temp())
    temperatures.append(temp())

plt.plot(range(100), TT1[:100], label='T1')
plt.plot(range(100), TT2[:100], label='T2')
plt.legend()
plt.show()

plt.plot(range(100), entropies[:100], label='S')
plt.plot(range(100), ent1[:100], label='S1')
plt.plot(range(100), ent2[:100], label='S2')
plt.legend()
plt.show()

plt.plot(range(100), temperatures)
plt.show()
