from matplotlib import pyplot as plt 
import pandas as pd 

dataInit = pd.read_csv('dataInitCanonical.csv', header=None)
dataFinal = pd.read_csv('dataFinalCanonical.csv', header=None)

plt.subplot(1, 2, 1)
plt.imshow(dataInit.to_numpy(), interpolation='nearest')
plt.xlabel('Initial')
plt.subplot(1, 2, 2)
plt.imshow(dataFinal.to_numpy(), interpolation='nearest')
plt.xlabel('Final')
plt.show()
