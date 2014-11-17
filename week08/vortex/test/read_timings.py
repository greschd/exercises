#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    13.11.2014 09:13:49 CET
# File:    read_timings.py

import sys
sys.path.append('../../../python_tools')
from plot_setup import *

import os
import numpy as np
import matplotlib.pyplot as plt

directory = '../res'

weak = []
strong = []
for filename in os.listdir(directory):
    with open(directory + '/' + filename) as f:
        for line in f.readlines():
            line = filter(None, line.split('\n'))[0]
            curr = {}
            for pair in filter(None, line.split(', ')):
                try:
                    curr[pair.split(': ')[0]] = int(pair.split(': ')[1])
                except:
                    curr[pair.split(': ')[0]] = float(pair.split(': ')[1])
            if(filename.split('_')[0] == 'weak'):
                weak.append(curr)
            elif(filename.split('_')[0] == 'strong'):
                strong.append(curr)


def plot_strong():
    x = [m['nproc'] for m in strong]
    y = [1 / m['time'] for m in strong]
    fig, ax = plt.subplots()
    for m in strong:
        if(m['nproc'] == 1):
            serial = 1 / m['time']

    xopt = np.linspace(0, 50, 100)
    yopt = serial * xopt
    ax.plot(x, y, 'o', label='measured')
    ax.plot(xopt, yopt, label='linear scaling')
    ax.set_xlim(0.5, 48.5)
    ax.set_xlabel('\# cores')
    ax.set_ylabel('inverse runtime', rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.04)
    ax.text(0.5, 1.08, '$N = 10080$, $\delta t = 0.01$, 50 steps',
         horizontalalignment='center',
         fontsize=20,
         transform=ax.transAxes)
    plt.savefig('../../pdf/plots/strong.pdf', bbox_inches='tight')
    fig.clf()
def plot_weak():
    x = [m['nproc'] for m in weak]
    y = [1 / m['time'] for m in weak]
    fig, ax = plt.subplots()

    #~ xopt = np.linspace(0, 50, 100)
    #~ yopt = serial * xopt
    ax.plot(x, y, 'o', label='measured')
    #~ ax.plot(xopt, yopt, label='linear scaling')
    #~ ax.set_xlim(0.5, 48.5)
    ax.set_xlabel('\# cores')
    ax.set_ylabel('inverse runtime', rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.04)
    ax.text(0.5, 1.08, '$N = 10080$, $\delta t = 0.01$, 50 steps',
         horizontalalignment='center',
         fontsize=20,
         transform=ax.transAxes)
    plt.savefig('../../pdf/plots/weak.pdf', bbox_inches='tight')
    plt.show()
    fig.clf()


if __name__ == "__main__":
    plot_strong()
    plot_weak()
    print("read_times.py")
    
