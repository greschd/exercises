#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    19.10.2014 12:22:42 CEST
# File:    plot_count.py

import sys
sys.path.append("../../python_tools")
from plot_setup import *

import numpy as np

    
    
if __name__ == "__main__":
    with open('counts.txt', 'r') as f:
        data = list(filter(None,f.read().split(', ')))

    for i in range(len(data)):
        data[i] = int(data[i])
    
    maxval = max(data)

    yval = [0 for i in range(maxval + 1)]
    for val in data:
        yval[val] += 1

    textstr = 'avg: ' + str(sum(data) / len(data))
    textstr += '\npeak: ' + str(np.argmax(yval))
    textstr += '\nmedian: ' + str(int(np.median(data)))
    textstr += '\nmin: ' + str(min(data))
    textstr += '\nmax: ' + str(max(data))
    textstr += '\n' + r'$\sigma$: ' + str(int(np.std(data)))

    fig, ax = plt.subplots(1)
    ax.hist(data, 250, color='b', normed = True)
    props = dict(boxstyle='round', facecolor='#cccccc', alpha=0.5)
    ax.text(0.65, 0.95, textstr, transform=ax.transAxes, fontsize=14, verticalalignment='top', bbox = props)
    plt.xlabel(r'# steps', fontsize = 15)
    plt.ylabel('occurrence probability (per 100 steps)', fontsize=15, rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.05)
    fig.savefig('../pdf/counts.pdf')
    
    
