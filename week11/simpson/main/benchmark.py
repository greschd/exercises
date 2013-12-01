#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    01.12.2013 17:38:04 CET
# File:    benchmark.py

import sys
import os
import numpy as np
import matplotlib.pyplot as plt
import pylab

# turns the characters from the file into numbers
def to_number(string):
    try:
        res = int(string)
        return res
    except:
        pass
    try:
        res = float(string)
        return res
    except:
        return string


# compiles and executes "cpp_name.cpp" for each function and saves the results into "file_name.txt"
def measure(cpp_name, file_name):
    fct = ["one", "onex", "xsquare", "mysin"]
    
    # setting up the various flags and defines for compiling
    
    os.system("rm " + file_name + ".txt")
    
    compiler = "g++"
    
    flags = " -std=c++11 -Wall -O3 -funroll-loops"
    
    variables = " -DLOW=0 -DHIGH=10 -DNZERO=10 -DSTEPS=100 -DREPEATS=1000"
    
    name = cpp_name
    
    path = "../main/"
    
    
    for f in fct:
        cmd = compiler + flags + " " + path + name + ".cpp -o " + name + "_" + f + " -DFUN=" + f + variables
        err = os.system(cmd)
        if err != 0:
            print(err)
        cmd = "./" + name + "_" + f
        err = os.system(cmd)
        if err != 0:
            print(err)
    
    f = file(file_name + ".txt")
    lines = f.readlines()
    f.close()
    
    
    entries = [];
    
    for l in lines:
        entries.append(l[:-1].split())
    
    num = [[to_number(entries[j][i]) for i in range(1,len(entries[0]))] for j in range(len(entries))]
    res = np.array(num)
    return res

# plots the timing results for a specific function (->index) with "title" as plot title and saved as "name.pdf"
def plot(name, index, title, res_h, res_fp, res_fo, res_v):
    #------------------------ plot ----------------------- 
    plt.title(title)
    plt.grid(True)
    plt.xlabel("N")
    plt.ylabel("time")
    plt.plot(res_h[0,:], res_h[index,:],'r+', label = "hard-coded")
    plt.plot(res_fp[0,:], res_fp[index,:],'b+', label = "function pointer")
    plt.plot(res_fo[0,:], res_fo[index,:],'g+', label = "function object")
    plt.plot(res_v[0,:], res_v[index,:],'y+', label = "virtual function")
    plt.legend(bbox_to_anchor = (1, .3), loc = 5)

    #------------------- save the plot ------------------- 
    pylab.savefig(name + ".pdf")
    plt.clf()

def main():
    res_h = measure("hard_coded", "res_h")
    print "measured the hard-coded version" 
    
    res_fp = measure("function_pointer", "res_fp")
    print "measured the function pointer version"
    
    res_fo = measure("function_object", "res_fo")
    print "measured the function object version"
    
    res_v = measure("virtual", "res_v")
    print "measured the virtual function version"
    
    plot("one", 1, "f(x) = 1", res_h, res_fp, res_fo, res_v)
    
    plot("onex", 2, "f(x) = x", res_h, res_fp, res_fo, res_v)
    
    plot("xsquare", 3, "f(x) = x^2", res_h, res_fp, res_fo, res_v)
    
    plot("sin", 4, "f(x) = sin(x)", res_h, res_fp, res_fo, res_v)
    print "plots done"
    


if __name__ == "__main__":
    print("benchmark.py")
    main()
