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

s1_init = spins_init[:40][:]
s2_init = spins_init[40:][:]
s1_end = spins_end[:40][:]
s2_end = spins_end[40:][:]

plt.subplot(1, 2, 1)
plt.imshow(s1_init, cmap=cmap1, interpolation='nearest')
plt.xlabel('S1')
plt.subplot(1, 2, 2)
plt.imshow(s2_init, cmap=cmap2, interpolation='nearest')
plt.xlabel('S2')
plt.suptitle("Before contact")
plt.show()

plt.subplot(1, 2, 1)
plt.imshow(s1_end, cmap=cmap2, interpolation='nearest')
plt.xlabel('S1')
plt.subplot(1, 2, 2)
plt.imshow(s2_end, cmap=cmap2, interpolation='nearest')
plt.xlabel('S2')
plt.suptitle("After contact")
plt.show()

'''
plt.plot(range(len(data['E1'])), data['E1'])
plt.show()

plt.subplot(1, 2, 1)
plt.plot(data['E1'], data['S1'])
plt.subplot(1, 2, 2)
plt.plot(data['E2'], data['S2'])
plt.show()
'''