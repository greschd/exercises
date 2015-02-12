#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    09.03.2014 23:58:20 CET
# File:    measure.py

import sys
import os
import subprocess
import numpy as np
from math import log10, floor
from python_tools.py2tex import p2t

# rounding a value to its error, the error to 1 significant digit
def roundtoerr(val, err):
    # catch division by 0
    if(err == 0):
        return[val, err]
    else:
        val = round(val, int(floor(1 - log10(err))))
        err = round(err, int(floor(1 - log10(err))))
    return [val, err]

# compile poly.c using flags
def compile_poly(flags, defines):
    os.system("g++ " + flags + defines + " ../poly/poly.c -o poly.out")

# measure for size N
def measure(N, tol, num_runs = 1):
    command = "./poly.out " + str(N)
    res = []
    for j in range(num_runs):
        rvalue = subprocess.check_output(command, shell = True).split()
        res.append([float(i) for i in rvalue]) # [N, performance, op count, runtime, rerr] 
        if res[j][4] > tol:
            print("Results do not match!")
    mean = [sum(res[j][i] for j in range(len(res)))/num_runs for i in range(len(res[0]))]
    
    # return values and errors for num_runs > 1
    if(num_runs > 1):
        err = [np.sqrt(sum((res[j][i] - mean[i])**2 for j in range(len(res)))/ (num_runs - 1)) for i in range(len(res[0]))]
        return [roundtoerr(mean[i], err[i]) for i in range(len(mean))] 
    # return values only for num_runs = 1 (error not defined)
    else:
        return mean

if __name__ == "__main__":
    flags = "-O3 -fno-tree-vectorize -mno-abm -DMEASURE"
    defines = [[" -DCOST='(N*(N+1)/2+N+1)' -DFUNC=poly", "poly"], [" -DCOST='2*N' -DFUNC=horner", "horner"], [" -DCOST='2*N' -DFUNC=horner2", "horner2"]]
    for d in defines:
        compile_poly(flags, d[0])
        tol = 1e-6
        sizes = [2**i for i in range(7, 12)]
        r = [measure(n, tol, 10) for n in sizes]
        
        # formatting
        data = [[r"size $N$", "performance [flop/cycle]", "op count", "runtime [kcycles]"]]
        for datapoint in r:
            data.extend([[int(datapoint[0][0]), str(datapoint[1][0]).strip('0').rstrip('.') + r"$\pm$" + str(datapoint[1][1]).strip('0').rstrip('.') , int(datapoint[2][0]), str(datapoint[3][0]/1e3).strip('0').rstrip('.') + r"$\pm$" + str(datapoint[3][1]/1e3).strip('0').rstrip('.')]])
        p2t(np.transpose(data).tolist(), "measurement_" + d[1], topline = False, bottomline = False, rightline = False, leftline = False)
    
    print("measure.py")
