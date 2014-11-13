#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    13.11.2014 09:13:49 CET
# File:    read_times.py

import sys
sys.path.append('../../../python_tools')
from plot_setup import *

import os
import numpy as np
import matplotlib.pyplot as plt

directory = './res'

data = []

for filename in os.listdir(directory):
    with open(directory + '/' + filename) as f:
        for line in f.readlines():
            curr = {'np': int(filename.lstrip('t_').rstrip('.txt'))}
            for pair in filter(None, line.split(', ')):
                try:
                    curr[pair.split(': ')[0]] = int(pair.split(': ')[1])
                except:
                    curr[pair.split(': ')[0]] = float(pair.split(': ')[1])
            data.append(curr)


def plot(size, ax):
    maximum = 0
    for point in data:
        if(point['mesh'] == size):
            if(point['np'] == 1):
                perf = 1 / point['time']
                maximum = max(perf, maximum)
                steps = point['steps']
                ax.plot(point['np'], perf, 'bo', label='measured')
                x = np.linspace(0, 50, 100)
                ax.plot(x, perf * x, 'r', label='linear scaling')
            else:
                perf = 1 / point['time']
                maximum = max(perf, maximum)
                ax.plot(point['np'], perf, 'bo')
    ax.legend(loc='upper left')
    ax.set_xlim(0.5, 48.5)
    ax.set_ylim(0, 2 * maximum)
    ax.set_xlabel('\# cores')
    ax.set_ylabel('inverse runtime', rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.04)
    ax.text(0.5, 1.08, 'mesh=' + str(size) + 'x' + str(size) + ', \# steps=' + str(steps),
         horizontalalignment='center',
         fontsize=20,
         transform=ax.transAxes)
    #~ ax.set_title('mesh=' + str(size) + 'x' + str(size) + ', \# steps=' + str(steps))


for i, size in enumerate([128, 256, 1024, 2048]):
    fig, ax = plt.subplots()
    plot(size, ax)
    plt.savefig('../plots/t_' + str(size) + '.pdf')
    plt.clf()

if __name__ == "__main__":
    print("read_times.py")
    
