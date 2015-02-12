#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    14.03.2014 23:56:53 CET
# File:    main.py

import sys
import os
import numpy as np
import matplotlib.pyplot as plt

def mean(data):
    n = len(data)
    m = len(data[0])
    res = []
    for i in range(m):
        res.append(sum(data[j][i] for j in range(n))/n)
    return res
    
def var(data, meanval):
    n = len(data)
    m = len(meanval)
    err = [np.sqrt(sum((data[i][j] - meanval[j])**2  for i in range(n))) / (n - 1) for j in range(m)]
    return err
    
def binning_analysis(data):
    n = int(np.log2(len(data)))
    data = data[:pow(2,n)]
    meanval = mean(data)
    errs = []
    x = range(n - 2)
    for i in x:
        data = [[(data[2*j][m] + data[2*j + 1][m]) / 2. for m in range(len(data[0]))] for j in range(int(len(data) / 2))]
        errs.append(var(data, meanval))
    
    plt.figure()
    plt.title("relative error in " + r"$E_{pot}$ = " + str(round(meanval[0],3)), fontsize = 16, fontweight = "bold")
    plt.grid(True)
    plt.plot(x, [e[0] / meanval[0] for e in errs], "o")
    plt.xlabel("bin nr.", fontsize = 14, fontweight = "bold")
    plt.savefig("epot.pdf")
    plt.clf()
    plt.title("relative error in " + r"$E_{kin}$ = " + str(round(meanval[1],3)), fontsize = 16, fontweight = "bold")
    plt.plot(x, [e[1] / meanval[1] for e in errs], "o")
    plt.xlabel("bin nr.", fontsize = 14, fontweight = "bold")
    plt.grid(True)
    plt.savefig("ekin.pdf")
        

if __name__ == "__main__":
    # converting to a python list
    f = open("data.txt", "r")
    lines = f.readlines()
    f.close()
    
    entries = [l.rstrip("\n").split(" ") for l in lines]
    data = [[float(x) for x in e]for e in entries]
    binning_analysis(data)
    
# strangely i get different results in different measurements, but the error seems to converge
    
    
