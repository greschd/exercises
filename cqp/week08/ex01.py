#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    10.04.2014 15:26:54 CEST
# File:    ex01.py

import sys
import numpy as np
import scipy.linalg as la
import matplotlib.pyplot as plt

alpha = [13.00773, 1.962079, 0.444529, 0.1219492]
N = 4

def construct_matrix(f):
    M = [list(range(N)) for i in range(N)]
    for i in range(N):
        for j in range(N):
            M[i][j] = f(i, j)
    return M
    
def get_S():
    return construct_matrix(lambda i, j: (np.pi / (alpha[i] + alpha[j]))**(3/2.))

def get_T():
    return construct_matrix(lambda i, j: 3 * (np.pi**(3/2.) * alpha[i] * alpha[j])/(alpha[i] + alpha[j])**(5/2.))
    
def get_A():
    return construct_matrix(lambda i, j: - 2 * np.pi / (alpha[i] + alpha[j]))
    
def eigval():
    return la.eigh(np.array(get_T()) + np.array(get_A()), np.array(get_S()))
    
def plot():
    chi = lambda a, x: np.exp(-a * x**2)
    E, v = eigval()
    x = np.linspace(-5, 5, 200)
    S = get_S()
    for i in range(N):
        plt.plot(x, [1 / sum(v[i, j] * S[j][j] for j in range(N)) * sum(v[i,j] * chi(alpha[j], xval) for j in range(N)) for xval in x])
    plt.show()


    
plot()
    
