# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt


ori = np.loadtxt("RadialVelocities.dat")



rta = np.loadtxt("modelo.txt")
cons = np.loadtxt("rta.txt")

plt.scatter(ori[:,0], ori[:,1], label = "Datos")
mb = cons[0]**2
md = cons[1]**2
mh = cons[2]**2
plt.plot(rta[:,0], rta[:,1], color = 'r', label = "Modelo, Mb = %.2f, Mh = %.2f, Mh = %.2f" %(mb,md,mh))    
plt.xlabel("Radio [kpc]")
plt.ylabel("Velocidad radial [km/s]")
plt.title("Velocidad radial contra radio")
plt.legend(loc=0)
plt.savefig("modelo.png")
