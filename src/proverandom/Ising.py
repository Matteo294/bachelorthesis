import numpy as np 
from matplotlib import pyplot as plt
import IsingClass as IC
import random

Ncycles = int(3e4)
Nspins = 100
Temp = -0.1
Ntemp = 10
H = 1
J = 0

# Create Ising system (see IsingClass.py)
S = IC.IsingCanonical(N=Nspins, T=Temp, J=J, H=H)

# Stores energies during MC cycles

# Cycles over different values of temperature
temperatures = [-500, -100, -20, -1, -0.1, 0.1, 1, 20, 100, 500]
avgE = []
for T in temperatures:
    print("T :", T)
    # Prepare things for the next simulation
    energy_old = S.Hamiltonian()
    energies = []
    energy = []
    S.T = T
    S.thermalize()
    # Monte Carlo cycles
    for n in range(Ncycles):
        if n % 1000 == 0:
            pass
            #print(str(int(n/Ncycles*100)) + "%")
        idx = random.randint(0, Nspins - 1)
        S.flip(idx)
        energy_new = S.Hamiltonian()
        if T < 0:
            if energy_new > energy_old or np.exp((energy_old - energy_new)/S.T) > random.uniform(0, 1):
                energy_old = energy_new
            else:
                S.flip(idx)
        else:
            if energy_new < energy_old or np.exp((energy_old - energy_new)/S.T) > random.uniform(0, 1):
                energy_old = energy_new
            else:
                S.flip(idx)
        energies.append(energy_old)
        energy.append(np.mean(energies))
    avgE.append(energy[-1])

    print("Number spins up", S.nplus, "Percentage spins up", 100*S.nplus/S.N)
    print("\n")

#plt.plot(range(Ncycles), energy)
#plt.plot(range(Ncycles), energies)
#plt.show()

plt.plot(temperatures, avgE)
plt.show()