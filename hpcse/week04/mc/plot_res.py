#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    19.10.2014 16:36:03 CEST
# File:    plot_res.py

import sys
sys.path.append("../../python_tools")
from plot_setup import *

import os
import numpy as np

if __name__ == "__main__":

    nthreads = []
    res = []
    for filename in os.listdir('./res'):
        with open('./res/' + filename, 'r') as f:
            nthreads.append(int(filename.split('.txt')[0]))
            res.append(float(f.read()))

    idx = np.argsort(nthreads)
    nthreads = np.array(nthreads)[idx]
    res = np.array(res)[idx]
    inv_runtime = 1. / res

    fig, ax = plt.subplots(1)
    ax.plot(nthreads, inv_runtime, 'o', label = 'measured')
    ax.plot(nthreads, [inv_runtime[0] * n for n in nthreads], label='optimum')

    plt.xlabel(r'\# threads', fontsize = 15)
    plt.ylabel('inverse runtime', fontsize=15, rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.05)
    plt.savefig('../pdf/res.pdf')
    
    print("plot_res.py")
    
