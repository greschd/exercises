#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    01.03.2014 17:53:00 CET
# File:    measure.py

import sys
import os
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import pickle

frequency = 3.06e9

def compile_mvm(num_runs, flags):
    os.system("g++ " + flags + " ../src/mvm.c -DNUM_RUNS=" +str(num_runs) + " -o mvm.out")

def measure(m, n):
    command = "./mvm.out " + str(m) + " " + str(n)
    rvalue = subprocess.check_output(command, shell = True).split()
    res = [float(i) for i in rvalue] # [rdtsc, clock, gettimeofday] time used
    return res
    
def measurement(sizes, num_runs,  flags, name):
    compile_mvm(num_runs, flags)
    res = []
    for s in sizes:
        res.append(measure(s, s))
        print(str(s) + " done")
    res = np.array(res).transpose()
    f = open("data" + name + ".txt", "wb")
    pickle.dump([sizes, res, flags], f)
    f.close()

def plot(name):
    r = open("data" + name + ".txt", "rb")
    [sizes, res, flags] = pickle.load(r)
    r.close()
    
    # runtime (in Mcycles)

    f, ax = plt.subplots()
    
    ax.text(0, 1.15, "MVM runtime " , fontsize = 18, fontweight = "bold", alpha = 1, transform = ax.transAxes)
    ax.text(0,-0.35, "system: Ubuntu 13.10 on Intel Core 2 Duo @3.06 GHz\ncompiler: gcc v4.8.1\nflags: " + flags, bbox=dict(facecolor='white', alpha=1, boxstyle = 'round'), transform = ax.transAxes)
    f.subplots_adjust(bottom = 0.25, top = 0.85)
    
    ax.grid(True)
    ax.plot(sizes, res[0]/1e6, marker = "o")
    ax.set_xlabel("matrix / vector size", fontsize = 15, horizontalalignment = "right")
    ax.set_ylabel("runtime [Mcycles]", fontsize = 15, rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.05)
    ax.xaxis.set_label_coords(1, -0.07)
    
    plt.savefig("../../latex/MVM_runtime" + name + ".pdf")

    # 2 * N ** 2 [flop / issue] /(issues / cycle) -> flop / cycle
    g, bx = plt.subplots()
    
    bx.text(0, 1.15, "MMM flops per cycle " , fontsize = 18, fontweight = "bold", alpha = 1, transform = bx.transAxes)
    bx.text(0,-0.35, "system: Ubuntu 13.10 on Intel Core 2 Duo @3.06 GHz\ncompiler: gcc v4.8.1\nflags: " + flags, bbox=dict(facecolor='white', alpha=1, boxstyle = 'round'), transform = ax.transAxes)
    g.subplots_adjust(bottom = 0.25, top = 0.85)
    
    bx.grid(True)
    bx.plot(sizes, [2*sizes[i]**2/(res[0][i]) for i in range(0, len(sizes))], marker = "o")
    bx.set_xlabel("matrix / vector size", fontsize = 15, horizontalalignment = "right")
    bx.set_ylabel("flops/cycle", fontsize = 15, rotation = "horizontal", horizontalalignment = "left")
    bx.yaxis.set_label_coords(0, 1.05)
    bx.xaxis.set_label_coords(1, -0.07)
    
    plt.savefig("../../latex/MVM_flops" + name + ".pdf")
    
    # % of peak performance
    h, cx = plt.subplots()
    
    cx.text(0, 1.15, "MVM % of peak performance ", fontsize = 18, fontweight = "bold", alpha = 1, transform = cx.transAxes)
    cx.text(0,-0.35, "system: Ubuntu 13.10 on Intel Core 2 Duo @3.06 GHz\ncompiler: gcc v4.8.1\nflags: " + flags, bbox=dict(facecolor='white', alpha=1, boxstyle = 'round'), transform = ax.transAxes)
    h.subplots_adjust(bottom = 0.25, top = 0.85)
    
    cx.grid(True)
    cx.plot(sizes, [100*sizes[i]**2/(res[0][i]) for i in range(0, len(sizes))], marker = "o")
    cx.set_xlabel("matrix / vector size", fontsize = 15, horizontalalignment = "right")
    cx.set_ylabel("% of peak performance", fontsize = 15, rotation = "horizontal", horizontalalignment = "left")
    cx.yaxis.set_label_coords(0, 1.05)
    cx.xaxis.set_label_coords(1, -0.07)
    
    plt.savefig("../../latex/MVM_percentage" + name + ".pdf")
    
if __name__ == "__main__":
    flags = [["-Wall -O3 -fno-tree-vectorize -mno-abm", "O3"],["-Wall -fno-tree-vectorize -mno-abm", ""]]
    sizes = range(100, 1501, 100)
    measurement(sizes, 500, flags[1][0], flags[1][1])
    measurement(sizes, 500, flags[0][0], flags[0][1])
    plot(flags[1][1])
    plot(flags[0][1])
    
    print("measure.py")
