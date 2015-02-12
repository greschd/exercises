#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    01.03.2014 17:53:00 CET
# File:    measure.py

# call this from the build folder to execute the measurements and produce the plots

import sys
import os
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import pickle

frequency = 3.06e9

# compile mmm.c, num_runs defining number of runs for each measurement
def compile_mmm(num_runs, flags):
    os.system("g++ " + flags + " ../src/mmm.c -DNUM_RUNS=" +str(num_runs) + " -o mmm.out")

# measures time for each of the 3 clocks (sizes m x k and k x n)
def measure(m, k, n):
    command = "./mmm.out " + str(m) + " " + str(k) + " " + str(n)
    rvalue = subprocess.check_output(command, shell = True).split()
    res = [float(i) for i in rvalue] # [rdtsc, clock, gettimeofday] time used
    return res

# measures for each of the entries of sizes
def measurement(sizes, num_runs, flags, name):
    compile_mmm(num_runs, flags)
    res = []
    for s in sizes:
        res.append(measure(s, s, s))
        print(str(s) + " done")
    res = np.array(res).transpose()
    f = open("data" + name + ".txt", "wb")
    pickle.dump([sizes, res, flags], f)
    f.close()

# creates the plots for runtime, flops/s and percentage of the peak performance
def plot(name):
    r = open("data" + name + ".txt", "rb")
    [sizes, res, flags] = pickle.load(r)
    r.close()
    
    # runtime (in Gcycles)
    f, ax = plt.subplots()
    
    ax.text(0, 1.15, "MMM runtime", fontsize = 18, fontweight = "bold", alpha = 1, transform = ax.transAxes)
    ax.text(0,-0.3, "system: Ubuntu 13.10 on Intel Core 2 Duo @3.06 GHz\ncompiler: gcc v4.8.1\nflags: " + flags, bbox=dict(facecolor='white', alpha=1, boxstyle = 'round'), transform = ax.transAxes)
    f.subplots_adjust(bottom = 0.25, top = 0.85)
    
    ax.grid(True)
    ax.plot(sizes, res[0]*frequency / 1e9, label="rdtsc Clock", marker = 'o')
    ax.plot(sizes, res[1]*frequency / 1e9, label="C Clock", marker = 'o')
    ax.plot(sizes, res[2]*frequency / 1e9, label="gettimeofday", marker = 'o')
    ax.set_xlabel("matrix size", fontsize = 15, horizontalalignment = "right")
    ax.set_ylabel("runtime [Gcycles]", fontsize = 15, rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.05)
    ax.xaxis.set_label_coords(1, -0.07)
    ax.legend(loc = "lower right", fancybox = True)
    plt.savefig("../../latex/MMM_runtime" + name + ".pdf")

    # 2 * N ** 3 [flop / issue] /(issues / cycle) -> flop / cycle
    g, bx = plt.subplots()
    
    bx.text(0, 1.15, "MMM flops per cycle", fontsize = 18, fontweight = "bold", alpha = 1, transform = bx.transAxes)
    bx.text(0,-0.3, "system: Ubuntu 13.10 on Intel Core 2 Duo @3.06 GHz\ncompiler: gcc v4.8.1\nflags: " + flags, bbox=dict(facecolor='white', alpha=1, boxstyle = 'round'), transform = ax.transAxes)
    g.subplots_adjust(bottom = 0.25, top = 0.85)
    
    bx.grid(True)
    bx.plot(sizes, [2*sizes[i]**3/(res[0][i]*frequency) for i in range(0, len(sizes))], label="rdtsc Clock", marker = "o")
    bx.plot(sizes, [2*sizes[i]**3/(res[1][i]*frequency) for i in range(0, len(sizes))], label="C Clock", marker = "o")
    bx.plot(sizes, [2*sizes[i]**3/(res[2][i]*frequency) for i in range(0, len(sizes))], label="gettimeofday", marker = "o")
    bx.set_xlabel("matrix size", fontsize = 15, horizontalalignment = "right")
    bx.set_ylabel("flops/cycle", fontsize = 15, rotation = "horizontal", horizontalalignment = "left")
    bx.yaxis.set_label_coords(0, 1.05)
    bx.xaxis.set_label_coords(1, -0.07)
    
    bx.legend(loc = "center right", fancybox = True)
    plt.savefig("../../latex/MMM_flops" + name + ".pdf")
    
    # peak performance: 2 flop / cycle -> % of peak performance = 50 * (flop / cycle)
    h, cx = plt.subplots()
    
    cx.text(0, 1.15, "MMM % of peak performance", fontsize = 18, fontweight = "bold", alpha = 1, transform = cx.transAxes)
    cx.text(0,-0.3, "system: Ubuntu 13.10 on Intel Core 2 Duo @3.06 GHz\ncompiler: gcc v4.8.1\nflags: " + flags, bbox=dict(facecolor='white', alpha=1, boxstyle = 'round'), transform = ax.transAxes)
    h.subplots_adjust(bottom = 0.25, top = 0.85)
    
    cx.grid(True)
    cx.plot(sizes, [100*sizes[i]**3/(res[0][i]*frequency) for i in range(0, len(sizes))], label="rdtsc Clock", marker = "o")
    cx.plot(sizes, [100*sizes[i]**3/(res[1][i]*frequency) for i in range(0, len(sizes))], label="C Clock", marker = "o")
    cx.plot(sizes, [100*sizes[i]**3/(res[2][i]*frequency) for i in range(0, len(sizes))], label="gettimeofday", marker = "o")
    cx.set_xlabel("matrix size", fontsize = 15, horizontalalignment = "right")
    cx.set_ylabel("% of peak performance", fontsize = 15, rotation = "horizontal", horizontalalignment = "left")
    cx.yaxis.set_label_coords(0, 1.05)
    cx.xaxis.set_label_coords(1, -0.07)
    plt.xlabel("matrix size", fontsize = 14)
    
    cx.legend(loc = "center right", fancybox = True)
    plt.savefig("../../latex/MMM_percentage" + name + ".pdf")
    
if __name__ == "__main__":
    flags = "-Wall -O3 -fno-tree-vectorize -mno-abm"
    name = "O3"
    num_runs = 1
    sizes = range(100, 1501, 100)
    measurement(sizes, num_runs, flags, name)
    plot(name)
    
    print("measure.py")
