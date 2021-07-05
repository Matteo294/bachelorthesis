from matplotlib import pyplot as plt
from matplotlib.pyplot import cm
from matplotlib import colors
import pandas as pd 
import numpy as np

cmap = colors.ListedColormap(['deepskyblue','red', 'red'])
bounds = [-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)

dataInit = pd.read_csv('dataInitCanonical.csv', header=None)
dataFinal = pd.read_csv('dataFinalCanonical.csv', header=None)
data = pd.read_csv('energies.csv', header=None)

data = data.to_numpy()
edges = np.linspace(-50, 50, 20)
plt.hist(data, bins=edges)
plt.show()


plt.imshow(dataInit.to_numpy(), interpolation='nearest', cmap=cmap, norm=norm)
ax = plt.gca()
ax.set_yticklabels([])
ax.set_xticklabels([])
ax.set_xticks([])
ax.set_yticks([])
plt.show()

plt.imshow(dataFinal.to_numpy(), interpolation='nearest', cmap=cmap, norm=norm)
ax = plt.gca()
ax.set_yticklabels([])
ax.set_xticklabels([])
ax.set_xticks([])
ax.set_yticks([])
plt.show()