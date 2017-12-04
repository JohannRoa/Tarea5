import numpy as np
import matplotlib.pylab as plt
modelo=np.genfromtxt('parametros.dat')
datos=np.genfromtxt('RadialVelocities.dat')
r=datos[:,0]
v=datos[:,1]
plt.scatter(r,v,label='datos',c='red')
plt.plot(r, modelo,label='modelo')
plt.xlabel('r(kpc)')
plt.ylabel('v(km/s)')
plt.legend()
plt.savefig('modelo.png')


