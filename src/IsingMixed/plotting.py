import pandas as pd 
from matplotlib import pyplot as plt

data = pd.read_csv("data.csv")

plt.plot(range(len(data['E1'])), data['E1'])
plt.show()

plt.subplot(1, 2, 1)
plt.plot(data['E1'], data['S1'])
plt.subplot(1, 2, 2)
plt.plot(data['E2'], data['S2'])
plt.show()