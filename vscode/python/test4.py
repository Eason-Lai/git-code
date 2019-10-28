import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
def getCynByAxis(redius, heightStart, heightEnd, offset, devision, mainAxis):
    

    mainAxis = mainAxis.lower()

    theta = np.linspace(0, 2*np.pi, devision)
    cx = np.array([redius * np.cos(theta)]) 
    cz = np.array([heightStart, heightEnd])
    cx, cz = np.meshgrid(cx, cz)
    cy = np.array([redius * np.sin(theta)] * 2)

    if mainAxis == 'z':
        return offset[0] + cx, offset[1] + cy, offset[2] + cz
    elif mainAxis == 'y':
        return offset[0] + cx, offset[1] + cz, offset[2] + cy
    elif mainAxis == 'x':
        return offset[0] + cz, offset[1] + cy, offset[2] + cx
    else:
        raise ValueError("'x', 'y' or 'z' PLZ")

def drawCylinder():
    

    fig = plt.figure(figsize = (6, 10))
    ax = plt.axes(projection = '3d')
    ax.set_xlim(-5, 5)
    ax.set_ylim(-5, 5)
    ax.set_zlim(-5, 5)

    cx, cy, cz = getCynByAxis(offset = [-3, 0, 0], devision = 40,\
        mainAxis = 'x', heightEnd = 6, heightStart = 0,\
        redius = 0.5)
    ax.plot_surface(cx, cy, cz, rstride = 1, cstride = 1,\
        linewidth = 0, alpha = 0.25)

    cx, cy, cz = getCynByAxis(offset = [0, 0, -3], devision = 40,\
        mainAxis = 'z', heightEnd = 6, heightStart = 0,\
        redius = 0.5)
    ax.plot_surface(cx, cy, cz, rstride = 1, cstride = 1,\
        linewidth = 0, alpha = 0.25)
    
    plt.show()

if __name__ == '__main__':
    drawCylinder()
