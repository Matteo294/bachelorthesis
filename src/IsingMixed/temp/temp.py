from matplotlib import pyplot as plt
import pandas as pd 
import numpy as np

data1 = pd.read_csv('data1.csv')
data2 = pd.read_csv('data2.csv')

S1_after = data2['S1']
S1_before = data1['S1']
S2_after = data2['S2']
S2_before = data1['S2']

E1_after = data2['E1']
E1_before = data1['E1']
E2_after = data2['E2']
E2_before = data1['E2']

T1 = [(Eb - Ea) / (Sb - Sa)  for Ea, Eb, Sa, Sb in zip(E1_before, E1_after, S1_before, S1_after) if (Eb - Ea) != 0]
T2 = [(Eb - Ea) / (Sb - Sa)  for Ea, Eb, Sa, Sb in zip(E2_before, E2_after, S2_before, S2_after) if (Eb - Ea) != 0]

avgT1 = [0]
for i in range(len(T1)):
    avgT1.append((avgT1[-1] + T1[i]) / (i+1)) 
#plt.plot(range(len(T1)), T1)
plt.plot(range(len(avgT1))[1000:], avgT1[1000:])
plt.show()