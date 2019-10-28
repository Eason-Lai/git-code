import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from math import pi
from numpy import cos,sin
import numpy as np
import math
from collections import Counter
from matplotlib import cm
from dask.array.creation import meshgrid
from statsmodels.graphics.plottools import rainbow

fig = plt.figure()
ax = Axes3D(fig)
u = np.linspace(0,2*pi,50)
h = np.linspace(-5,5,20)
h1 = np.linspace(-5,5,20)
R = 1
#x**2+y**2=1
X1 = np.outer(np.cos(u)*R,np.ones(len(h)))
Y1 = np.outer(np.sin(u)*R,np.ones(len(h)))
Z1 = np.outer(np.ones(len(u)),h)      

#x**2+z**2=1
X2 = np.outer(np.cos(u),np.ones(len(h)))
Z2 = np.outer(np.sin(u),np.ones(len(h)))
Y2 = np.outer(np.ones(len(u)),h)  

X3 = np.ones(len(h))
Y3 = X3*0
Z3 = Y3  

X1 = np.row_stack((X1,X3))
Y1 = np.row_stack((Y1,Y3))
Z1 = np.row_stack((Z1,Z3))

X = np.row_stack((X1,X2))
Y = np.row_stack((Y1,Y2))
Z = np.row_stack((Z1,Z2))

#交线
x3 = np.cos(u)
y3 = np.sin(u)
z31 = (1-x3**2)**0.5
z32 = -(1-x3**2)**0.5



             

ax.set_xlim(-6,6)
ax.set_ylim(-6,6)
ax.set_zlim(-6,6)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

# ax.plot_surface(X1, Y1, Z1, rstride=1, cstride=1, linewidth = 0, alpha = 0.8,color = "black")
# ax.plot_surface(X2, Y2, Z2, rstride=1, cstride=1, linewidth = 0, alpha = 0.6)
# ax.plot(x3, y3, z31, color='black')
# ax.plot(x3, y3, z32, color='black')
ax.plot_surface(X, Y, Z, alpha = 0.6,rstride=1,cstride=1,linewidth = 0,color='Grey',antialiased=True)

#ax.plot_wireframe(X, Y, Z, alpha = 0.6)
#ax.scatter(X, Y, Z)
plt.show()