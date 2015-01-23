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
import matplotlib.pyplot as plt

if __name__ == "__main__":
    name = sys.argv[1].split('.txt')[0]
    with open(name + ".txt", "r") as f:
        disk_lists = [np.array(eval(x)) for x in f.read().split('\n') if x]

    for i, disk_list in enumerate(disk_lists):
        d0 = 0.5 / 100.

        fig = plt.figure()
        axis = fig.add_subplot(111, aspect='equal')
        #~ plt.xlim(0, 1)
        #~ plt.ylim(0, 1)
        axis.plot(disk_list[:, 0], disk_list[:, 1], 'ko', markersize = 1.2)

        if(len(disk_lists) > 1):
            plt.savefig(name + "_" + str(i) + ".pdf", bbox_inches = 'tight')
        else:
            plt.savefig(name + ".pdf", bbox_inches = 'tight')

    print("plot.py")
