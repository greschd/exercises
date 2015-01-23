#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    30.11.2013 00:52:03 CET
# File:    plot.py

import sys

import numpy as np
import matplotlib.pyplot as plt
import pylab

def plot_size():
    #----------------------- input ----------------------- 
    ios1 = open("../build/size_0.txt", 'r')
    data1 = np.loadtxt(ios1, skiprows = 1)
    ios1.close()
    
    #----------------------- input ----------------------- 
    ios2 = open("../build/size_9.txt", 'r')
    data2 = np.loadtxt(ios2, skiprows = 1)
    ios2.close()
    
    #------------------------ plot ----------------------- 
    plt.title("p1 = 0.075, p2 = 0.085")
    plt.grid(True)
    plt.xlabel("years")
    plt.ylabel("population size")
    plt.yscale('log')
    plt.plot(data1[:,0], data1[:,1],'r+', label = "min_age = 0")
    plt.plot(data2[:,0], data2[:,1],'b+', label = "min_age = 9")
    plt.legend(bbox_to_anchor = (1, .3), loc = 5)

    #------------------- save the plot ------------------- 
    pylab.savefig("../build/population_size.pdf")
    plt.clf()


if __name__ == "__main__":
    print("plot.py")
    plot_size()
    
