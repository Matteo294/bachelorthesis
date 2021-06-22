import numpy as np
import pandas as pd 
from matplotlib import pyplot as plt

data0 = pd.read_csv('data0.csv')
data1 = pd.read_csv('data1.csv')
plt.plot(data0['n'], data0['Energies'])
plt.plot(data1['n'], data1['Energies'])
plt.show()