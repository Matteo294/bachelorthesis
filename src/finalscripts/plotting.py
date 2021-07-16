import pandas as pd 
from matplotlib import pyplot as plt
import numpy as np
import seaborn as sns

from matplotlib import colors
cmap1 = colors.ListedColormap(['red', 'blue'])
cmap2 = colors.ListedColormap(['blue', 'red'])

spins_init = pd.read_csv('initconf.csv', header=None)
spins_end = pd.read_csv('endconf.csv', header=None)

spins_init = spins_init.to_numpy()
spins_end = spins_end.to_numpy()

s1_init = spins_init[:200][:]
s2_init = spins_init[200:][:]
s1_end = spins_end[:200][:]
s2_end = spins_end[200:][:]

cmap = colors.ListedColormap(['white','red', 'royalblue'])
bounds = [-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)

plt.imshow(s1_init, cmap=cmap, norm=norm, interpolation='nearest')
plt.xlabel(r'$S_1$', fontsize=16)
ax = plt.gca()
ax.set_yticklabels([])
ax.set_xticklabels([])
ax.set_xticks([])
ax.set_yticks([])
plt.show()

plt.imshow(s2_init, cmap=cmap, norm=norm, interpolation='nearest')
plt.xlabel(r'$S_2$', fontsize=16)
ax = plt.gca()
ax.set_yticklabels([])
ax.set_xticklabels([])
ax.set_xticks([])
ax.set_yticks([])
plt.show()

plt.imshow(s1_end, cmap=cmap, norm=norm, interpolation='nearest')
plt.xlabel(r'$S_1$', fontsize=16)
ax = plt.gca()
ax.set_yticklabels([])
ax.set_xticklabels([])
ax.set_xticks([])
ax.set_yticks([])
plt.show()

plt.imshow(s2_end, cmap=cmap, norm=norm, interpolation='nearest')
plt.xlabel(r'$S_2$', fontsize=16)
ax = plt.gca()
ax.set_yticklabels([])
ax.set_xticklabels([])
ax.set_xticks([])
ax.set_yticks([])
plt.show()
