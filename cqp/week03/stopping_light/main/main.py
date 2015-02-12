#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    06.03.2014 08:30:18 CET
# File:    main.py

import sys
import numpy as np
import scipy.linalg as la
import matplotlib.pyplot as plt
import scipy.constants as sc
import matplotlib.animation as anim
import pickle

def init(interval, N, k0, x0, a):
    X = np.linspace(interval[0], interval[1], N)
    norm_const = (2/(sc.pi * a**2))**(0.25)
    psi = [norm_const * np.exp(1j * k0 * x)*np.exp(-(x-x0)**2 / a**2) for x in X]
    return np.array(psi)
    

def Hamiltonian(interval, N, V = lambda x: 0):
    # set up kinetic part
    H = 2* np.eye(N)
    for i in range(1, N):
        H[i - 1, i] = - 1
        H[i, i - 1] = - 1
    
    H /= (float(interval[1] - interval[0]) / N)**2
    # add potential
    x = np.linspace(interval[0], interval[1], N)
    for i in range(len(x)):
        H[i,i] += V(x[i])
    return H


def evolve(interval, N, tinterval, tN, k0, x0, a, V = lambda x: 0, method = "diag"):
    deltat = float(tinterval[1] - tinterval[0])/(tN - 1)
    
    if(method == "taylor"):
        Hexp = np.eye(N) - 1j * deltat * Hamiltonian(interval, N, V)
    
    elif(method == "directintegration"):
        Hexp1 = np.eye(N) - 1j * deltat / 2. * Hamiltonian(interval, N, V)
        Hexp2 = np.eye(N) + 1j * deltat / 2. * Hamiltonian(interval, N, V)
    
    else:
        Hexp = la.expm((-1j*deltat)*Hamiltonian(interval, N, V))
    
    psivalues = []
    psi = init(interval, N, k0, x0, a)
    psivalues.append(psi)
    for i in range(0, tN - 1):
        if(method == "directintegration"):
            psi = la.solve(Hexp2,Hexp1.dot(psi))
        else:
            psi = Hexp.dot(psi)
        psivalues.append(psi)
    return psivalues
    
def hardwall_measure(method):
    
    # enter values
    interval = [-50, 0]
    N = 400
    k0 = 5
    x0 = -10
    a = 1
    tinterval = [0, 5]
    tN = 201
    # ------------
    
    tvalues = np.linspace(tinterval[0], tinterval[1], tN)
    psivalues = evolve(interval, N, tinterval, tN, k0, x0, a, method = method)
    
    f = open("hardwall_" + method + ".txt", "wb")
    pickle.dump([psivalues, interval, N], f)
    f.close
    

def tiltedwall_measure(method):
    
    # enter values
    interval = [-50, 20]
    N = 400
    k0 = 5
    x0 = -10
    a = 1
    tinterval = [0, 6]
    tN = 101
    alpha = 6
    # ------------
    
    def V(x):
        if x < 0:
            return 0
        else:
            return alpha * x
    
    tvalues = np.linspace(tinterval[0], tinterval[1], tN)
    psivalues = evolve(interval, N, tinterval, tN, k0, x0, a, V, method = method)
    
    f = open("tiltedwall_" + method + ".txt", "wb")
    pickle.dump([psivalues, interval, N], f)
    f.close


def animate(name, title, part = "re", method = "diag", show = False):
    
    r = open(name + "_" + method + ".txt", "rb")
    [psivalues, interval, N] = pickle.load(r)
    r.close()
    
    fig = plt.figure()
    if(part != "density"):
        ax = plt.axes(xlim=(interval[0], interval[1]), ylim=(-1, 1))
    else:
        ax = plt.axes(xlim=(interval[0], interval[1]), ylim=(0, 0.7))
    fig.suptitle(title, fontsize = 18, fontweight = "bold")
    ax.set_xlabel(r"$x$", fontsize = 15)
    if(part == "re"):
        ax.set_ylabel(r"$Re[\Psi(x)]$", fontsize = 15)
    elif(part == "im"):
        ax.set_ylabel(r"$Im[\Psi(x)]$", fontsize = 15)
    else:
        ax.set_ylabel(r"$(\Psi(x))^2$", fontsize = 15)
    line, = ax.plot([],[])
    
    x = np.linspace(interval[0], interval[1], N)
    def animate(i):
        if(part == "re"):
            y = psivalues[i].real
        elif(part == "im"):
            y = psivalues[i].imag
        else:
            y = abs(psivalues[i])**2
        line.set_data(x, y)
        return line,
    
    dpi = 200
    writer = anim.writers['ffmpeg'](fps=30)
    ani = anim.FuncAnimation(fig, animate, interval = 50, frames = len(psivalues), blit = False)
    ani.save(name + "_" + part + "_" + method + ".mp4", fps=30, dpi = dpi, writer = writer)
    if(show):
        plt.show()
    
if __name__ == "__main__":
    hardwall_measure("diag")
    hardwall_measure("taylor")
    hardwall_measure("directintegration")
    tiltedwall_measure("diag")
    animate("hardwall", "wave packet between hard walls, matrix - exp as Taylor", method = "taylor" , part = "re")
    animate("hardwall", "wave packet between hard walls, direct num. integration", method = "directintegration" , part = "re")
    animate("hardwall", "wave packet between hard walls, explicit diagonalization", part = "re")
    animate("hardwall", "wave packet between hard walls", part = "density")
    animate("tiltedwall", "wave packet hits a tilted wall", part = "density")
    animate("tiltedwall", "wave packet hits a tilted wall", part = "re")
    print("main.py")
    
# the freely moving wave packet gets chirped over time due to dispersion
# on a hard wall, there is a phase shift of pi (boundary condition: wfct = 0)
# on a tilted wall, the higher - k parts of the wave penetrate the wall more (and stay there longer)
# hence the peak gets higher after hitting the wall.

