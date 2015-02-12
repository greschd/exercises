#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    18.02.2014 22:58:32 CET
# File:    numerov.py

import sys
import numpy as np
import scipy.constants as spc
import cmath 
import matplotlib.pyplot as plt

# calculates the next step in the numerov algorithm
def numerov_step(k0, k1, k2, psi0, psi1, deltax):
    temp = deltax ** 2 / 12
    # solving the numerov equation for psi_n+1 
    return (2 * (1 - 5 * temp * k1) * psi1 - (1 + temp * k0) * psi0) / (1 + temp * k2)

# calculates the vector for the wave function psi
def numerov(V, E, m, psi0, psi1, xmin, xmax, N):
    deltax = (xmax - xmin)/N
    
    # creating the list of solutions (containing only inital values)
    psi = [psi0, psi1]
    
    # creating the k - vector
    x = np.linspace(xmin, xmax, N)
    k = [(2 * m * (E - V(j))) / spc.hbar ** 2 for j in x]
    
    # appending the steps to the solution
    for i in xrange(2, N):
        psi.append(numerov_step(k[i - 2], k[i - 1], k[i], psi[-2], psi[-1], deltax))
    
    return psi

# calculates the transmission probability over a barrier
def barrierT(V, E, m, a, N):
    # cutting off V at 0, a
    def potential(x):
        if(x <= 0 or x >= a):
            return 0
        else:
            return V(x)
    
    deltax = a / (N - 2)
    q = np.sqrt(2 * m * E)/spc.hbar
    
    psi = numerov(potential, E, m, cmath.exp(complex(0, q*deltax)), 1, -deltax, a + deltax, N)
    
    M = np.array([[1, 1], [cmath.exp(complex(0, -q * deltax)), cmath.exp(complex(0, q * deltax))]])
    A = np.linalg.solve(M,[psi[-2],psi[-1]])
    return (1/abs(A[0])) ** 2

if __name__ == "__main__":
    
    # "reasonable" values for a and m (give a nice curve for the exact formula)
    a = 1e-19
    mass = spc.m_e
    
    # vectors for energy and number of bins
    E = np.linspace(0.001, 0.99, 100)
    N = [3, 5, 10, 100]

    def potT(E, V, N):
        return barrierT(V, E, mass, a, N)

    # first potential 
    V1 = lambda x: 1

    def pot1T_exact(E):
        k = np.sqrt(2 * mass * (1 - E))/spc.hbar
        return 1/ (1 + (np.sinh(k * a) ** 2 / (4 * E * (1 - E))))
        
    exact = [pot1T_exact(x) for x in E]
    approx = [[potT(e, V1, n) for e in E] for n in N]
    
    plt.figure()
    plt.plot(E, exact, label = "exact solution")
    for i in xrange(0, len(N)):
        plt.plot(E, approx[i], label = "N = " + str(N[i]))
        plt.legend(loc = "lower right")
        plt.xlabel("E", fontsize = 14)
        plt.ylabel("T", fontsize = 14)
        plt.suptitle("Transmission probability: step potential", fontsize = 14)
        plt.savefig("pot1.pdf")
    
    
    # second potential
    V2 = lambda x: 4 / a * x * (1 - x / a)
    
    approx = [[potT(e, V2, n) for e in E] for n in N]
    
    plt.figure()
    plt.plot(E, exact, label = "step potential")
    for i in xrange(0, len(N)):
        plt.plot(E, approx[i], label = "N = " + str(N[i]))
        plt.legend(loc = "lower right")
        plt.xlabel("E", fontsize = 14)
        plt.ylabel("T", fontsize = 14)
        plt.suptitle("Transmission probability: parabolic potential", fontsize = 14)
        plt.savefig("pot2.pdf")

    print("numerov.py")
    


