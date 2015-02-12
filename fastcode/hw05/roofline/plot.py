#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    03.04.2014 03:16:13 CEST
# File:    plot.py

import sys
import matplotlib.pyplot as plt
import numpy as np

def plot():
    x = np.linspace(0.01, 100, 100)
    pi = [3 for i in x]
    beta = [8 * i for i in x]
    piprime = [2 for i in x]
    
    f, ax = plt.subplots()
    
    ax.text(0, 1.15, "Roofline Plot " , fontsize = 18, fontweight = "bold", alpha = 1, transform = ax.transAxes)

    ax.text(0.6, 0.9, r"$\pi = 3$" + " flops / cycle", transform = ax.transAxes, color = "blue", fontsize = 15)
    ax.text(0.6, 0.78, r"$\pi' = 2$" + " flops / cycle", transform = ax.transAxes, color = "red", fontsize = 15)
    ax.text(0.28, 0.65, r"$\beta = 8 $" + " bytes / cycle", transform = ax.transAxes, color = "green", fontsize = 15)    
    ax.text(0.16, 0.48, r" $I = 1/32$, " + r"$\pi'' = 1/4$", transform = ax.transAxes, color = "red", fontsize = 15)
    f.subplots_adjust(bottom = 0.1, top = 0.85)
    
    ax.grid(True)
    ax.loglog(x, pi)
    ax.loglog(x, beta)
    ax.loglog(x, piprime)
    ax.loglog([1/32.],[1/4.], marker = 'o', color = "red")
    ax.set_ylim(1e-2,6)
    ax.set_xlabel("operational intensity [flops/byte]", fontsize = 15, horizontalalignment = "right")
    ax.set_ylabel("performance [flops/cycle]", fontsize = 15, rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.05)
    ax.xaxis.set_label_coords(1, -0.07)
    
    plt.savefig("../latex/roofline.pdf")
    
    
if __name__ == "__main__":
    plot()
    print("plot.py")
