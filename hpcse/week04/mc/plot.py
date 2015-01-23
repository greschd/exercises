#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    18.10.2014 03:13:53 CEST
# File:    plot.py

import sys
sys.path.append("../../python_tools")
from plot_setup import *

import numpy as np

if __name__ == "__main__":
    with open('data.txt', 'r') as f:
        data = f.read().split('\n')

    N = []
    res = []
    var = []

    
    for line in data:
        linedata = list(filter(None, line.split(', ')))
        if(len(linedata) == 3):
            N.append(int(linedata[0]))
            res.append(float(linedata[1]))
            var.append(float(linedata[2]))

    stddev = [np.sqrt(variance) for variance in var]
    mean_err = [np.sqrt(var[i] / N[i]) for i in range(len(N))]

    ax = plt.subplot(111)
    ax.set_xscale("log")
    #~ plt.errorbar(N, res, yerr=stddev, label='standard deviation', fmt='o')
    plt.errorbar(N, res, yerr=mean_err, label='standard error of the mean', fmt='o')
    #~ plt.legend()
    plt.xlabel('N', fontsize = 15)
    ax.axhline(0.3, color = 'r')
    plt.ylabel(r'$\rho$', fontsize=15, rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.05)
    plt.savefig('../pdf/rho.pdf')
    plt.clf()

    ax = plt.subplot(111)
    plt.xlabel('N', fontsize = 15)
    plt.ylabel('real error / SEM', fontsize=15, rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.05)
    ax.set_xscale('log')
    ax.set_yscale('log')
    plt.plot(N, [abs(res[i] - 0.3) / mean_err[i] for i in range(len(res))], 'o')
    plt.axhline(1, color='r')
    plt.savefig('../pdf/error.pdf')

    
