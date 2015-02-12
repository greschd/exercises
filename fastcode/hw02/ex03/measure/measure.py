#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    12.03.2014 19:27:01 CET
# File:    measure.py

import sys
import os
import subprocess
import numpy as np
from python_tools.py2tex import p2t
from python_tools.round2err import rnd2errlist, avg_err
import pickle

def compile_superslow(name):
    os.system("make -C ../superslow/ -f make_" + name + ".mk")

def measure(num_runs = 1, name = ""):
    command = "./../superslow/driver_" + name 
    res = []
    for j in range(num_runs):
        print(j)
        res.append( subprocess.check_output(command, shell = True).split())
    w = open("data" + name + ".txt", "wb")
    pickle.dump([res, num_runs], w)
    w.close()

# converting the data into avg & err, then string
def convert(name = ""):
    r = open("data" + name + ".txt", "rb")
    [res, num_runs] = pickle.load(r)
    r.close()
    data = []
    for run in res:
        temp = []
        for i in range(0, len(run) , 4):
            temp2 = []
            for j in range(0, 4, 2):
                temp2.append([int(float(run[i + j])), float(run[i + j + 1])])
            temp.append(temp2)
        data.append(temp)
        
    n = len(data[0]) # number of implementations
    m = len(data[0][0]) # number of measured sizes
    
    data2 = []
    for i in range(n):
        temp = []
        for j in range(m):
            temp.extend([data[k][i][j][1] for k in range(num_runs)])
        data2.append(temp)
    
    avgdata = [avg_err(impl) for impl in data2]
    
    return rnd2errlist(avgdata)
    
if __name__ == "__main__":
    compile_superslow("opt")
    measure(5, "opt")
    compile_superslow("noopt")
    measure(5, "noopt")
    p2t(np.transpose([convert("noopt"), convert("opt")]).tolist(), "table",topline = False, bottomline = False, rightline = False, leftline = False)
