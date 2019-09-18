from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from funcs import *
import numpy as np

#defining lines : x(k) = A + k*l
A1 = np.array([1,-2,4]).reshape((3,1))
l1 = np.array([1,-2,3])
A2 = np.array([2,-1,-7]).reshape((3,1))
l2 = np.array([2,-1,-1])

n  = np.cross(l1,l2)
print(n)

P = np.array([1,-1,-1]).reshape((3,1))
Q = np.array([1,3,-7]).reshape((3,1))


#creating x,y for 3D plotting
len = 10
xx, yy = np.meshgrid([-2,3], [-2,5])
#setting up plot
fig = plt.figure()
ax = fig.add_subplot(111,projection='3d',aspect='equal')

c  = (P.T)@n
#print(c)
N=np.linalg.norm(n)
M=c-(Q.T)@n

d=np.linalg.norm(M/N)
print(d)
l3 = n.reshape((3,1))
A=Q-d*l3/N

print(A)

l1 = np.array([1,-2,3]).reshape((3,1))
l2 = np.array([2,-1,-1]).reshape((3,1))

l1_p = line_dir_pt(-l1/np.linalg.norm(l1),A1)
l2_p = line_dir_pt(-l2/np.linalg.norm(l2),A2)
l3_p = line_dir_pt(-l3*d/(10*N),Q)

#corresponding z for planes
z = ((c-n[0]*xx-n[1]*yy)*1.0)/(n[2])


ax.scatter(P[0],P[1],P[2],'o',label="Point P",color='r')
ax.scatter(Q[0],Q[1],Q[2],'o',label="Point Q")
ax.scatter(A[0],A[1],A[2],'o',label="Point A")

#plotting planes
ax.plot_surface(xx, yy, z, color='b',alpha=0.3)

#plotting line
plt.plot(l1_p[0,:],l1_p[1,:],l1_p[2,:],label="Line L1")
plt.plot(l2_p[0,:],l2_p[1,:],l2_p[2,:],label="Line L2")
plt.plot(l3_p[0,:],l3_p[1,:],l3_p[2,:],label="Line L3")

#show plot
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best');plt.grid()
plt.show()
