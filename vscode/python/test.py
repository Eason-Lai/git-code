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
R = 1
#x**2+y**2=1
X1 = np.outer(np.cos(u)*R,np.ones(len(h)))
Y1 = np.outer(np.sin(u)*R,np.ones(len(h)))
Z1 = np.outer(np.ones(len(u)),h)      

#x**2+z**2=1
X2 = np.outer(np.cos(u)*R,np.ones(len(h)))
Z2 = np.outer(np.sin(u)*R,np.ones(len(h)))
Y2 = np.outer(np.ones(len(u)),h)  

#交线
x3 = np.cos(u)
y3 = np.sin(u)
z31 = (1-x3**2)**0.5
z32 = -(1-x3**2)**0.5


X3 = np.outer(np.cos(u)*R,np.ones(len(h)))
Y3 = np.outer(np.sin(u)*R,np.ones(len(h)))
n = 0
for a in u:
    h = np.linspace(-sin(a),sin(a),20)
    if n == 0 : 
        Z3 = h
    else :
        Z3 = np.row_stack((Z3,h))
    n = n + 1


ax.set_xlim(-6,6)
ax.set_ylim(-6,6)
ax.set_zlim(-6,6)
ax.set_xlabel('x')
ax.set_ylabel('y')  
ax.set_zlabel('z')

# ax.plot_wireframe(X1,Y1,Z1,alpha = 0.5,color='b')
# ax.plot_wireframe(X2,Y2,Z2,alpha = 0.2,color='g')

# ax.plot_surface(X1,Y1,Z1,alpha = 0.3,color='Grey')
# ax.plot_surface(X2,Y2,Z2,alpha = 0.4,color='Blue')
ax.plot_surface(X3,Y3,Z3,alpha = 1,color='Blue')

ax.plot(x3, y3, z31, color='r')
ax.plot(x3, y3, z32, color='r')
#ax.plot_surface(X, Y, Z, rstride=1, cstride=1, linewidth = 0, alpha = 0.8)
#ax.scatter(X, Y, Z)
plt.show()