import matplotlib.pyplot as plt
from numpy import *

a = 1
M = 100


def f(x):
    if (x > 0.1 and x < 0.3):
        return 1.
    else:
        return 0.

def u0(x):
    return f(x)

def u1(xmin, t):
    return f(xmin-a*t)

def u2(xmax, t):
    return f(xmax-a*t)


def iterations_1(xmin, xmax, tmax, N):
    ht = tmax/N
    hx = (xmax-xmin)/M
    u = zeros([N, M])
    for i in range(0, N):
        u[0, i] = u0(xmin+i*hx)
    for j in range(0, N-1):
        u[j+1, 0] = u1(xmin, j*ht)
        for i in range(1, N):
            dudx = (u[j, i]-u[j, i-1])/hx
            u[j+1][i] = -a*dudx*ht+u[j][i]
    return u
def iterations_2(xmin, xmax, tmax, N):
    ht = tmax/N
    hx = (xmax-xmin)/M
    u = zeros([N, M])
    for i in range(0, N):
        u[0, i] = u0(xmin+i*hx)
    for j in range(0, N-1):
        for i in range(0,N-1):
            dudx = u[j,i+1]-u[j,i]/hx
            u[j+1,i] = -a*dudx*ht+u[j][i]
        u[j+1,N-1] = u2(xmax, j*ht)
    return u
xmin = 0
xmax = 1
tmax = 10
Z = iterations_1(xmin, xmax, tmax, M)
#print(Z)

# graph
fig = plt.figure()
ax3 = plt.axes(projection='3d')
xx = arange(xmin, xmax, (xmax-xmin)/M)
yy = arange(xmin, xmax, (xmax-xmin)/M)
X, Y = meshgrid(xx, yy)
ax3.plot_surface(X, Y, Z, cmap='rainbow')
plt.show()
