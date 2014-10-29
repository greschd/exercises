#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    29.10.2014 02:18:48 CET
# File:    plot.py

import sys
sys.path.append("../python_tools")
from plot_setup import *

import numpy as np
import matplotlib.cm as cmx
import matplotlib.pyplot as plt
import matplotlib.colors as colors

if __name__ == "__main__":
    name = sys.argv[1].split('.txt')[0]
    with open(name + ".txt", "r") as f:
        disk_lists = [np.array(eval(x)) for x in f.read().split('\n') if x]


    for i, disk_list in enumerate(disk_lists):
        cm = plt.get_cmap('gist_rainbow') 
        cNorm  = colors.Normalize(vmin=0, vmax=len(disk_list))
        scalarMap = cmx.ScalarMappable(norm=cNorm, cmap=cm)

        d0 = 0.875 / 14.

        fig = plt.figure()
        axis = fig.add_subplot(111, aspect='equal')
        plt.xlim(0, 1)
        plt.ylim(0, 1)
        neighbours = [(0, 0), (0, 1), (0, -1), (1, 0), (1, 1), (1, -1),
                      (-1, 0), (-1, 1), (-1, -1)]
        for i, pos in enumerate(disk_list):
            for displacement in neighbours:
                circle = plt.Circle(pos + displacement, 0.5 * d0, color=scalarMap.to_rgba(i))
                dot = plt.Circle(pos + displacement, 0.05 * d0, color='k')
                axis.add_artist(circle)
                axis.add_artist(dot)

        if(len(disk_lists) > 1):
            plt.savefig(name + "_" + str(i) + ".pdf", bbox_inches='tight')
        else:
            plt.savefig(name + ".pdf", bbox_inches='tight')

    print("plot.py")
