import numpy as np 
from matplotlib import pyplot as plt
from matplotlib import colors
import seaborn as sns 
from matplotlib import animation
from IPython import display
import matplotlib.gridspec as gridspec

cmap = colors.ListedColormap(['royalblue','red', 'white'])
bounds = [-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)
Writer = animation.writers['ffmpeg']
writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)

class IsingCanonical:
    def __init__(self, nspins, B, T):
        self.spins = np.ones((nspins, nspins))
        self.nspins = nspins
        self.B = B 
        self.T = T
        self.nup = nspins*nspins
        self.E = -nspins*nspins*B

    def flip(self, idx1, idx2):
        deltaE = 2*self.spins[idx1][idx2]
        if self.spins[idx1][idx2] > 0:
            self.nup -= 1
        else:
            self.nup += 1
        self.spins[idx1][idx2] = -self.spins[idx1][idx2]
        self.E += deltaE
        return deltaE

nspins = 200
ncycles = int(1e6)
B = 1
T1 = -1e-10
T2 = 1000
S1 = IsingCanonical(nspins, B, T1)
S2 = IsingCanonical(nspins, B, T2)
fps=10000

fig = plt.figure()
plt.subplot(2, 2, 1)
im1 = plt.imshow(S1.spins, animated=True, cmap=cmap, norm=norm, interpolation='nearest') 
plt.subplot(2, 2, 2)
im2 = plt.imshow(S2.spins, animated=True, cmap=cmap, norm=norm, interpolation='nearest') 

def McCycle(frame=None, plotting=True):
    # S1
    idx1 = np.random.randint(0, nspins)
    idx2 = np.random.randint(0, nspins)
    deltaE = S1.flip(idx1, idx2)
    r = np.random.rand()
    if  (deltaE/S1.T < 0) or (np.exp(-deltaE/S1.T) > r):
        pass
    else:
        S1.flip(idx1, idx2)
    if plotting:
        im1.set_array(S1.spins)
    # S2
    idx1 = np.random.randint(0, nspins)
    idx2 = np.random.randint(0, nspins)
    deltaE = S2.flip(idx1, idx2)
    r = np.random.rand()
    if  (deltaE/S2.T < 0) or (np.exp(-deltaE/S2.T) > r):
        pass
    else:
        S2.flip(idx1, idx2)
    if plotting:
        im2.set_array(S2.spins)
        return im1,im2,

#anim = animation.FuncAnimation(fig, McCycle, frames=10000, interval=1000/fps, blit=True)
#plt.show()

for _ in range(ncycles):
    McCycle(plotting=False)

print("Done")

fig=plt.figure()
gs1 = gridspec.GridSpec(1, 2)
gs1.update(wspace=0, hspace=0) # set the spacing between axes.
ax1 = plt.subplot(1, 2, 1)
im1 = plt.imshow(S1.spins, animated=True, cmap=cmap, norm=norm, interpolation='nearest') 
ax2 = plt.subplot(1, 2, 2)
im2 = plt.imshow(S2.spins, animated=True, cmap=cmap, norm=norm, interpolation='nearest') 
ax1.set_yticklabels([])
ax1.set_xticklabels([])
ax1.set_xticks([])
ax1.set_yticks([])
ax2.set_yticklabels([])
ax2.set_xticklabels([])
ax2.set_xticks([])
ax2.set_yticks([])

def demonMcCycle(frame=None, plotting=True):
    global demon
    # S1
    idx1 = np.random.randint(0, 2*nspins)
    idx2 = np.random.randint(0, nspins)
    if idx1 >= nspins:
        deltaE = S2.flip(idx1-nspins, idx2)
    else:
        deltaE = S1.flip(idx1, idx2)
    r = np.random.rand()
    if (deltaE < 0):
        demon += abs(deltaE)
    elif abs(deltaE) < demon:
        demon -= deltaE
    else:
        if idx1 >= nspins:
            S2.flip(idx1-nspins, idx2)
        else:
            S1.flip(idx1, idx2)
    if plotting:
        im1.set_array(S1.spins)
        im2.set_array(S2.spins)
        return im1,im2,

demon = 0
anim = animation.FuncAnimation(fig, demonMcCycle, frames=100000, interval=1000/fps, blit=True)
anim.save('im.mp4', writer=writer)