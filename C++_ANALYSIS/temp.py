from numpy import *
""" Численное решение задачи Дирихле
для уравнения конвекции-диффузии в
прямоугольнике.Метод релаксации."""
def relaxation(b, f, I1, I2, n1, n2, omega, tol = 1.e-8):
         h2 = I1 / n1
         h3 = I2 / n2
         d = 2. / h2**2 + 2. / h3**2
         y = zeros([n1+1, n2+1])
         ff = zeros([n1+1, n2+1])
         bb = zeros([n1+1, n2+1])
         for j in arange(1,n2,1):
                  for i in arange(1,n1,1):
                           ff [i,j] = f(i*h2, j*h3)
                           bb[i,j] = b(i*h2, j*h3)                           
         #максимальное число итераций - 10000
         for k in arange(1, 10001,1):
                  rn = 0.
                  for j in arange(1,n2,1):
                           for i in arange(1,n1,1):                                    
                                    rr = - (y[i-1,j] - 2.*y [i, j] + y[i+1,j]) / h2**2 \
                                         - (y[i,j-1] - 2.*y [i,j] + y[i,j+1]) / h3**2 \
                                         + bb[i,j]*(y [i+1,j] - y [i-1,j]) / (2.*h2) - ff [i,j]                                    
                                    rn = rn + rr**2
                                    y[i,j] = y[i,j] - omega * rr / d
                  rn = rn*h2*h3
                  if rn < tol**2: return y, k                  
         print ('Метод релаксации не сходиться:')
         print ('после 10000 итерации остаток=',sqrt(rn))
import matplotlib.pyplot as plt
bcList = [0., 10.]
sglist = ['-','--']
kk = 0
for bc in bcList:         
         I1 = 1.
         I2 = 1.
         def f(x,y):
                  return 1.
         def b(x,y):                 
                  return bc
         n1 = 25
         n2 = 25
         m = 20
         om = linspace(1., 1.95, m)
         it = zeros(([m]))
         for k in arange(0,m,1):
                  omega = om[k]
                  y, iter = relaxation(b, f, I1, I2, n1, n2, omega, tol=1.e-6)
                  it[k] = iter
         s1= 'b =' + str(bc)
         sg = sglist[kk]
         kk = kk+1
         plt.plot( om,it, sg, label = s1)
plt.title("Число итераций метода релаксации\n для приближённого решения эллиптической задачи\n с использованием заданного параметра релаксации $\\omega$")
plt.xlabel('$\\omega$')
plt.ylabel('iterations')
plt.legend(loc=0)
plt.grid(True)
plt.show()