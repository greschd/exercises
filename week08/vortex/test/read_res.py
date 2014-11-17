#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    17.11.2014 12:50:08 CET
# File:    read_res.py

import matplotlib.pyplot as plt
import subprocess

with open('res.txt', 'r') as f:
    data = f.read()

data = filter(None, data.split('x, y, gamma'))
for i in range(len(data)):
    data[i] = filter(None, data[i].split('\n'))
    for j in range(len(data[i])):
        line = filter(None, data[i][j].split(', '))
        data[i][j] = {'x': float(line[0]), 'y': float(line[1]), 'gamma': float(line[2])}

fig, ax = plt.subplots()
size = 0.8
for i in range(len(data)):
    x = [p['x'] for p in data[i]]
    y = [p['y'] for p in data[i]]
    ax.plot(x, y, 'bo', markersize=0.2)
    ax.set_xlim(-size, size)
    ax.set_ylim(-size, size)
    plt.savefig('../plots/plot_' + str(i).rjust(3, '0') + '.png', dpi=900)
    ax.cla()

subprocess.call('avconv -r ' + str(int(len(data) / 2)) + ' -i ../plots/plot_%03d.png ../plots/vortices.mp4', shell=True)
