#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    18.02.2014 22:58:32 CET
# File:    numerov.py

import sys
import math as mth
import numpy as np
import scipy.optimize as opt
import cmath 
import matplotlib.pyplot as plt

# calculates the next step in the numerov algorithm
def numerov_step(k0, k1, k2, psi0, psi1, deltax):
    temp = deltax ** 2 / 12
    # solving the numerov equation for psi_n+1 
    return (2 * (1 - 5 * temp * k1) * psi1 - (1 + temp * k0) * psi0) / (1 + temp * k2)

# calculates the vector for the wave function psi
def numerov(V, E, m, psi0, psi1, xmin, xmax, N):
    deltax = (xmax - xmin)/ float(N)
    
    # creating the list of solutions (containing only inital values)
    psi = [psi0, psi1]
    
    # creating the k - vector
    x = np.linspace(xmin, xmax, N)
    k = [(2 * m * (E - V(j))) for j in x]
    
    # appending the steps to the solution
    for i in xrange(2, N):
        psi.append(numerov_step(k[i - 2], k[i - 1], k[i], psi[-2], psi[-1], deltax))
    
    return psi
    
# returns b s.t. V(b) = E
def getb(V, E):
    return opt.fsolve(lambda x: V(x) - E, 1)[0]

# returns the bins [x,y] wavefunctions PsiL(x), PsiR(y), g = Psi_L'/Psi_L - Psi_R'/Psi_R and the number of nodes: [[x,y], [PsiL,PsiR], g, nodes]
def shootingmethod(V, E, N):
    b = getb(V, E)
    m = 1
    hbar = 1
    k = np.sqrt(- 2 * m * E)
    
    
    # shooting from the left
    Nleft = int(max(mth.ceil(N * b), 3))
    deltaxleft = b / float(Nleft - 2)
    psiL = numerov(V, E, m, np.exp(- k * deltaxleft), 1, -deltaxleft, b, Nleft)
    
    # shooting from the right
    if(b != 1):
        Nright = int(max(mth.ceil(N * (1 - b)), 3))
        deltaxright = (1 - b) / float(Nright - 2) 
    else:
        Nright = 2
        deltaxright = 0.001
    VR = lambda x: V(1 - x) # potential as seen from the right
    psiR = numerov(V, E, m, np.exp(- k * deltaxright), 1, -deltaxright, (1 - b), Nright)
    psiR.reverse()
        
    
    # analyzing the left solution for number of sign changes
    nodes = 0
    for i in range(0, len(psiL) - 1):
        if(np.copysign(1, psiL[i]) != np.copysign(1, psiL[i + 1])):
            nodes += 1
            
    # getting g
    DL = (psiL[-1] - psiL[-2]) / deltaxleft
    DR = (psiR[1] - psiR[0]) / deltaxright
    g = (DL / psiL[-1]) - (DR / psiR[0])
    
    return [[np.linspace(-deltaxleft, b, Nleft).tolist(), np.linspace(b, 1 + deltaxright, Nright).tolist()],[psiL, psiR], g, nodes]

def geteigval(V, n, lowerbound, epsilon, N):
    Einterval = [lowerbound, 0]
    res = []
    while(Einterval[1] - Einterval[0] > epsilon):
        E = 0.5 * (Einterval[0] + Einterval[1])
        b = getb(V, E)
        res = shootingmethod(V, E, N)
        if(res[3] == n):
            # E is too low for positive g
            if(res[2] > 0):
                Einterval[0] = E
            # E is too high for negative g
            else:
                Einterval[1] = E
        # E is too high if the number of nodes is too high
        elif(res[3] > n):
            Einterval[1] = E
        # E is too low if the number of nodes is too low
        else:
            Einterval[0] = E
    return [E,res]

# calculates the eigenvalues of the harmonic potential, using N + 1 (or N) bins numerov, up to an error of epsilon
# solutions with energy > -epsilon will be ignored
def harmonicpot(c, N, epsilon):
    def V(x):
        if(x < 0 or 1 < x):
            return 0
        else:
            return c * (x**2 - x)
    
    upperbound = shootingmethod(V, -epsilon, N)
    maxN = 0
    if(upperbound[2] < 0):  # the actual eigenstate has lower energy
         maxN = upperbound[3]
    else:                   # the actual eigenstate doesn't exist
        maxN = upperbound[3] - 1 
    
    eigval = []
    lowerbound = - c / 4.0
    for n in range(0, maxN + 1): # n: eigenvalue index; N: number of bins
        eigval.append(geteigval(V, n, lowerbound, epsilon, N))
        lowerbound = eigval[-1][0] # only need to search above the last eigenvalue
    return eigval

def plot(c, N, epsilon):
    def V(x):
        if(x < 0 or 1 < x):
            return 0
        else:
            return c * (x**2 - x)
    result = harmonicpot(c, N, epsilon)
    
    plt.figure()
    plt.subplot(211)
    plt.suptitle("Eigenstates of the harmonic potential well for c = " + str(c), fontsize=14, fontweight='bold')
    for i in range(0, len(result)):
        e = '%+.2f' % result[i][0] # energy of the eigenstate
        plt.plot(result[i][1][0][0], np.array(result[i][1][1][0])/float(result[i][1][1][0][-1]), label=r"$\Psi_L$, n = " + str(i) + ", E = " + str(e))
        plt.plot(result[i][1][0][1], np.array(result[i][1][1][1])/float(result[i][1][1][1][0])) # no label here because I don't want the legend to be huge
    plt.legend(loc = "lower center", bbox_to_anchor = (0.5,-0.8), ncol = 2, fancybox = True )
    plt.xlabel(r"$x$", fontsize = 14)
    plt.ylabel(r"$\Psi(x)$", fontsize = 14)
    plt.grid(True)
    # naming convention is only good for integer c
    plt.savefig("c_" + str(c) + ".pdf")
    
    
if __name__ == "__main__":
    #-------------------------------------------#
    #             enter values here             #
    #-------------------------------------------#
    c = [0.1, 1, 10, 100, 400, 1000]
    N = 100
    epsilon = 1e-5
    #-------------------------------------------#
    
    for i in c:
        plot(i, N, epsilon)

    print("numerov.py")
    
# Interpretation: man sieht, dass es auch fuer sehr kleine Potentialtoepfe (theor.: beliebig klein) gebundene Zustaende gibt
# Fuer tiefere Potentialtoepfe kommen immer mehr gebundene Eigenzustaende hinzu. Der 0-te Eigenzustand wird dabei immer staerker lokalisiert
# (die Wellenfunktion zeigt einen staerkeren Peak in der Mitte, faellt gegen aussen schneller ab).
    


