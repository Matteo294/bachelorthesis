import numpy as np 
from matplotlib import pyplot as plt 
import matplotlib
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'

def T(E, N=1):
    return 1/np.log(((1-E)/E))

def S(E):
    return np.log(1/(1-E)) + E*np.log((1-E)/E)

Evals1 = np.linspace(0.49, 0.49999, 1000)
Evals2 = np.linspace(0.50001, 0.51, 1000)

plt.plot(Evals1, T(Evals1), 'black', linewidth=2.0)
plt.plot(Evals2, T(Evals2), 'black', linewidth=2.0)
plt.xlabel(r'$E/n\epsilon$', fontsize=16)
plt.ylabel(r'$\epsilon T \, / \, k_b$', fontsize=16)
ax = plt.gca()
ax.set_xticks([0.49, 0.5, 0.51])
ax.set_yticks([0])
ax.tick_params(axis='both', direction='in', bottom=True, top=False, left=True, right=False, labelbottom=True, labelleft=True)
plt.show()

Evals = np.linspace(1e-10, 1 - 1e-12, 1000)
plt.plot(Evals, S(Evals), 'black', linewidth=2.0)
t1=100
t2=len(Evals)-100
plt.scatter(Evals[t1], S(Evals[t1]), color='C0', s=30)
plt.text(Evals[t1+20], S(Evals[t1]),"T1",color='C0')
plt.scatter(Evals[t2], S(Evals[t2]), color='C1', s=30)
plt.text(Evals[t2+20], S(Evals[t2]),"T2",color='C1')
dx = Evals[1]-Evals[0]
dydx = np.gradient(S(Evals), dx)
print(dydx[t1])
deltaT=90

plt.plot(Evals[t1-deltaT:t1+deltaT],dydx[t1]*Evals[t1-deltaT:t1+deltaT] + S(Evals[t1])-dydx[t1]*Evals[t1],'--',color='C0')
plt.plot(Evals[t2-deltaT:t2+deltaT],dydx[t2]*Evals[t2-deltaT:t2+deltaT]+ S(Evals[t2])-dydx[t2]*Evals[t2],'--',color='C1')
plt.xlabel(r'$E \, / \, n\epsilon$', fontsize=16)
plt.ylabel(r'$S(E) \, / \, k_B$', fontsize=16)
ax = plt.gca()
#ax.set_xticks([0.49, 0.5, 0.51])
#ax.set_yticks([0])
ax.tick_params(axis='both', direction='in', bottom=True, top=False, left=True, right=False, labelbottom=True, labelleft=True)
plt.show()