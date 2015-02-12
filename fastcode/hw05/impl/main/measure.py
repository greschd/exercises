#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    02.04.2014 08:38:49 CEST
# File:    measure.py

import sys
import os
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import pickle

versions = ["V0", "V1", "V2", "V3", "FINAL"]

#--------------------------for code0 - code3----------------------------#
def compile_measure(nb, num_runs, flags, version):
    os.system("g++ " + flags + " ../measure/measure.cpp -DNUM_RUNS=" +str(num_runs) + " -DNB=" + str(nb) + " -D" + version + " -o " + version + "_" + str(nb) + ".out")

def measure(nb, version):
    command = "./" + version + "_" + str(nb) + ".out " 
    res = float(subprocess.check_output(command, shell = True))
    return res
    
def measurement(sizes, num_runs, flags, version):
    res = []
    for s in sizes:
        compile_measure(s, num_runs, flags, version)
        res.append(2. * s**3 / measure(s, version))
    return res

#----------------------------for finalcode------------------------------#
def compile_measure_final(n, num_runs, flags):
    os.system("g++ " + flags + " ../measure/measure_final.cpp -DNUM_RUNS=" + str(num_runs) + " -DN=" + str(n) + " -o final_" + str(n) + ".out")

def measure_final(n):
    command = "./final_" + str(n) + ".out " 
    res = float(subprocess.check_output(command, shell = True))
    return res
    
def measurement_final(sizes, num_runs, flags):
    res = []
    for s in sizes:
        compile_measure_final(s, num_runs, flags)
        res.append(2. * s**3 / measure_final(s))
    return res
    
def comparison_measurement():
    sizes = list(range(86, 1500, 86))
    
    resfinal = measurement_final(sizes, 10, flags)
    rescode0 = measurement(sizes, 1, flags, "V0")
    f = open("data.txt", "wb")
    pickle.dump([sizes, resfinal, rescode0], f)
    f.close()
    
def plot():
    r = open("data.txt", "rb")
    [sizes, final, code0] = pickle.load(r)
    r.close()
    
    f, ax = plt.subplots()
    
    ax.text(0, 1.15, "MMM flops per cycle " , fontsize = 18, fontweight = "bold", alpha = 1, transform = ax.transAxes)
    ax.text(0,-0.35, "system: Ubuntu 13.10 on Intel Core i7 (Haswell) @2.40 GHz\ncompiler: gcc v4.8.1\nflags: -Wall -std=c++11 -O3 -fno-tree-vectorize -mno-abm" , bbox=dict(facecolor='white', alpha=1, boxstyle = 'round'), transform = ax.transAxes)
    ax.text(0.3, 0.8, r"$\mathtt{finalcode.c}$", transform = ax.transAxes, color = "blue")
    ax.text(0.65, 0.2, r"$\mathtt{code0.c}$", transform = ax.transAxes, color = "green")
    f.subplots_adjust(bottom = 0.25, top = 0.85)
    
    ax.grid(True)
    ax.plot(sizes, final, marker = "o")
    ax.plot(sizes, code0, marker = "o")
    ax.set_xlabel("matrix size", fontsize = 15, horizontalalignment = "right")
    ax.set_ylabel("flops/cycle", fontsize = 15, rotation = "horizontal", horizontalalignment = "left")
    ax.yaxis.set_label_coords(0, 1.05)
    ax.xaxis.set_label_coords(1, -0.07)
    
    plt.savefig("../../latex/performance.pdf")
#--------------------------------plot-----------------------------------#
    
    
if __name__ == "__main__":
    flags = "-Wall -std=c++11 -O3 -fno-tree-vectorize -mno-abm"
    
    #~ print("L1: \n")
    #~ print("V1")
    #~ print(measurement([86], 10, flags,  "V1"))
    #~ print("V2")
    #~ print(measurement([86], 10, flags,  "V2"))
    #~ print("V3")
    #~ print(measurement([88], 10, flags,  "V3"))
    #~ print("measure.py")
    #~ 
    #~ print("L2: \n")
    #~ print("V1")
    #~ print(measurement([176], 10, flags,  "V1"))
    #~ print("V2")
    #~ print(measurement([176], 10, flags,  "V2"))
    #~ print("V3")
    #~ print(measurement([176], 10, flags,  "V3"))
    #~ print("measure.py")
    #~ 
    #~ comparison_measurement()
    plot()
    
