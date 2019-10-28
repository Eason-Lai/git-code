import numpy as np
from matplotlib import pyplot as plt
   
M1 = np.random.random((100,2))
M11 = np.column_stack((M1,np.ones(100)))
M2 = np.random.random((100,2)) - 0.7
M22 = np.column_stack((M2,np.ones(100)*(-1)))
MA = np.vstack((M11,M22))

plt.plot(M1[:,0],M1[:,1], 'ro')
plt.plot(M2[:,0],M2[:,1], 'go')
plt.show()
min_x = np.min(M2)
max_x = np.max(M1)
# 此处返回 x 是为了之后作图方便
x = np.linspace(min_x, max_x, 100)