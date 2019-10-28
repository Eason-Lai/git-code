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
u = np.linspace(0,2*pi,20)
h = np.linspace(-5,5,20)

#x**2+y**2=1
X1 = np.outer(np.cos(u),np.ones(len(h)))
Y1 = np.outer(np.sin(u),np.ones(len(h)))
Z1 = np.outer(np.ones(len(u)),h)      

#x**2+z**2=1
X2 = np.outer(np.cos(u),np.ones(len(h)))
Z2 = np.outer(np.sin(u),np.ones(len(h)))
Y2 = np.outer(np.ones(len(u)),h)  

#加入一条过渡线（点）,消除两圆柱线段跳跃产生的bug（该bug会产生两个风车扇叶）
X3 = np.ones(len(h))
Y3 = X3*0
Z3 = Y3  

#三个三维点阵两两合并
X1 = np.row_stack((X1,X3))
Y1 = np.row_stack((Y1,Y3))
Z1 = np.row_stack((Z1,Z3))

X = np.row_stack((X1,X2))
Y = np.row_stack((Y1,Y2))
Z = np.row_stack((Z1,Z2))

#设置坐标范围
ax.set_xlim(-6,6)
ax.set_ylim(-6,6)
ax.set_zlim(-6,6)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

#生成圆柱表面
ax.plot_surface(X, Y, Z, alpha = 1,rstride=1,cstride=1,linewidth = 0,color='Grey',antialiased=True)
ax.set_title('黎奕汛',fontproperties=font_set)

#输出
plt.show()