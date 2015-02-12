#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    01.03.2014 12:12:48 CET
# File:    measure.py

import sys
import numpy as np
import numpy.linalg as la
import matplotlib.pyplot as plt
import measure_lib as m

def eigs(k, cutoff):
    matrix = [[m.matrix_entry(i, j, k) for j in range(0, cutoff)] for i in range(0, cutoff)]
    [e,_] = la.eig(matrix)
    return sorted(e)
    
def plot(K, cutoff):
    e = []
    for k in K:
        e.append(eigs(k, cutoff))
    
    plt.figure()
    plt.grid(True)
    plt.suptitle("Cutoff at " + str(cutoff),fontsize=14, fontweight = "bold")
    plt.xlabel(r"$K$", fontsize = 14)
    plt.ylabel(r"$E$", fontsize = 14)
    for j in range(0, 5):
        plt.plot(K, [e[i][j] for i in range(0, len(e))])
    plt.savefig("cutoff_" + str(cutoff) + ".pdf")
        

if __name__ == "__main__":
    # enter variables here
    K = np.linspace(0, 5, 20)
    Cutoff = [5, 10, 50, 100]
    #---------------------
    
    for c in Cutoff:
        plot(K, c)
    
    print("measure.py")
    
# man sieht deutlich, wie das Mixing mit den hoeheren Zustaenden die Eigenenergie der tieferen Zustaende verringert.
    
