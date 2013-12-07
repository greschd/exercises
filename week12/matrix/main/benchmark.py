#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    06.12.2013 16:42:52 CET
# File:    benchmark.py

import sys
import os

def main():
    # versions of the matrix multiplication and the libraries they need to link with
    versions = [["simple",""],["meta",""],["blocking"," -DR=16"],["library"," -L/home/greschd/src/ATLAS_3.11/LINUX_13.04/lib/ -lf77blas -latlas -lgfortran"]]
    
    compiler = "g++"
    flags = " -std=c++11 -Wall -O3 -funroll-loops -ftemplate-depth=1500"
    
    variables = []
    
    for i in range(1, 10):
        num = str(2**i)
        iterations = str(2**(29 - 3 * i))
        variables.append(" -DN=" + num + " -DITER=" + iterations)
    
    for f in versions:
        print(f[0] + ":" )
        for v in variables:
            err = os.system(compiler + flags + " ../main/" + f[0] + ".cpp -o" + f[0] + ".x" + v + f[1])
            if err != 0:
                print err
            err = os.system("./" + f[0] + ".x")
            if err != 0:
                print err
    
    
    

if __name__ == "__main__":
    print("benchmark.py")
    main()
