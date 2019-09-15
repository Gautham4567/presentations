import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')

x = np.genfromtxt("meshX.dat")
y = np.genfromtxt("meshY.dat")
z = np.genfromtxt("meshz.dat")

ax.plot_surface(x, y, z, color='b',alpha=0.4)

L1_x=np.genfromtxt("meshX.dat")
L1_y=np.genfromtxt("meshL1_y.dat")
L1_z=np.genfromtxt("meshL1_z.dat")
L2_x=np.genfromtxt("meshX.dat")
L2_y=np.genfromtxt("meshL2_y.dat")
L2_z=np.genfromtxt("meshL2_z.dat")

plt.plot(L1_x[0,:],L1_y[0,:],L1_z[0,:])
plt.plot(L2_x[0,:],L2_y[0,:],L2_z[0,:])

P=np.genfromtxt("pointP.dat")
Q=np.genfromtxt("pointQ.dat")

ax.scatter(P[0],P[1],P[2],'o',label="Point P",color='r')
ax.scatter(Q[0],Q[1],Q[2],'o',label="Point Q",color='g')


plt.grid()
plt.show()
plt.xlabel('$x$')
plt.ylabel('$y$')
