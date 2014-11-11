#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    05.10.2014 21:39:02 CEST
# File:    read_res.py

import sys
import numpy as np
import matplotlib.pyplot as plt

def read(name, savename):
    f = open(name, "r")
    data = f.read()
    f.close()
    data = list(filter(None,data.split("end")))
    for i in range(len(data)): 
        data[i] = list(filter(None,data[i].split("\\")))
        for j in range(len(data[i])):
            data[i][j] = list(filter(None, data[i][j].split(" ")))
            for k in range(len(data[i][j])):
                data[i][j][k] = float(data[i][j][k])
    
    for i, matrix in enumerate(data):
        plt.imshow(matrix, extent = [-1, 1, -1, 1])
        plt.colorbar()
        plt.savefig(savename + "_" + str(i))
        plt.close()
        
    fig, axes = plt.subplots(2, 2)
    for i, ax in enumerate(axes.flat):
        im = ax.imshow(data[i], vmin = 0, vmax = 0.1, extent = [-1, 1, -1, 1])
    
    fig.subplots_adjust(right = 0.8)
    cbar_ax = fig.add_axes([0.85, 0.1, 0.05, 0.8])
    fig.colorbar(im, cax = cbar_ax)
    plt.savefig(savename + "_all")
    plt.close()

if __name__ == "__main__":
    read("test1.txt", "../plots/figure")
    print("read_res.py")
    
