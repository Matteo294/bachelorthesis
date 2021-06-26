import numpy as np
import pandas as pd 
from matplotlib import pyplot as plt

data0 = pd.read_csv('data0.csv')
print(data0['Energies'][0], data0['Energies'][-100:])
plt.plot(data0['n'], data0['Energies'])
plt.show()

data1 = pd.read_csv('data1.csv')
plt.plot(data1['n'], data1['Energies'])
plt.show()

data2 = pd.read_csv('data2.csv')
plt.plot(data2['n'], data2['Energies'])
plt.show()

data3 = pd.read_csv('data3.csv')
plt.plot(data3['n'], data3['Energies'])
plt.show()

data4 = pd.read_csv('data4.csv')
plt.plot(data4['n'], data4['Energies'])
plt.show()