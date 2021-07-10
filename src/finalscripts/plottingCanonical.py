from matplotlib import pyplot as plt
from matplotlib.pyplot import cm
from matplotlib import colors
import pandas as pd 
import numpy as np
import seaborn as sns

cmap = colors.ListedColormap(['white','red', 'royalblue'])
bounds = [-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)

dataInit = pd.read_csv('dataInitCanonical.csv', header=None)
dataFinal = pd.read_csv('dataFinalCanonical.csv', header=None)

from matplotlib import pyplot
pyplot.figure(figsize=(15, 15)) # width and height in inches
sns.heatmap(dataFinal, cbar=1, square=1, annot_kws={'size': 15}, cmap=colors.ListedColormap(['white', 'blue']))
plt.show()

plt.imshow(dataInit.to_numpy(), interpolation='nearest', cmap=cmap, norm=norm)
ax = plt.gca()
ax.set_yticklabels([])
ax.set_xticklabels([])
ax.set_xticks([])
ax.set_yticks([])
plt.show()

#pyplot.figure(figsize=(15, 15)) # width and height in inches
plt.imshow(dataFinal.to_numpy(), interpolation='nearest', cmap=cmap, norm=norm)
ax = plt.gca()
ax.set_yticklabels([])
ax.set_xticklabels([])
ax.set_xticks([])
ax.set_yticks([])
plt.show()