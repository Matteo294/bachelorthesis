import pandas as pd 
from matplotlib import pyplot as plt 
import numpy as np

data = pd.read_csv('data.csv')

plt.plot(data['Temperatures'], data['Energies'])
plt.show()