#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    06.12.2013 16:42:52 CET
# File:    benchmark.py

import sys
import os
import subprocess

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

def tune():
    # versions of the matrix multiplication, their flags and names (different block sizes)
    versions = []
    for i in range(2,9):
        num = str(2**i)
        versions.append(["blocking", " -DR=" + num, "Blocking with block size = " + num])
    
    # matrix sizes and the number of iterations for each matrix size
    variables = []
    for i in range(2, 11):
        num = 2**i
        iterations = 2**(29 - 3 * i + 1)
        variables.append([num, iterations])
        
    compiler = "g++"
    flags = " -std=c++11 -Wall -O3 -funroll-loops"
    
    # checking the speed of the versions 
    timings = []
    for f in versions:
        print(f[2] + ":" )
        for v in variables:
            print str(v[0]) + " - compiling.. "
            err = os.system(compiler + flags + " ../main/" + f[0] + ".cpp -o" + f[0] + ".x" + " -DN=" + str(v[0]) + " -DITER=" + str(v[1]) + f[1])
            if err != 0:
                print err
            print "running.. "
            res = str(subprocess.check_output("./" + f[0] + ".x")).split()
            timings.append([v[0], f[1], to_number(res[3])])
    
    # extracting fastest version
    optima = []
    for n in (row[0] for row in variables):
        tnew = filter(lambda item: item[0] == n, timings)
        optimum = sorted(tnew, key = lambda item: item[2])[0][1]
        optima.append([n, optimum])
        
    # write optima to file
    os.system("rm optima.txt")
    ios = open("optima.txt", 'w')
    for o in optima:
        ios.write(str(o[0]) + " " + o[1] + "\n")
    ios.close()
    
def measure():
    
    # get the optima from file
    f = file("optima.txt")
    lines = f.readlines()
    f.close()
    
    entries = []
    for l in lines:
        entries.append(l.split())
    
    optima = []
    for e in entries:
        optima.append([to_number(e[0]), " " + e[1]])
    
    # performing the measurements
    versions = [["simple","","simple version"],["meta","","meta-unroll-loop"],["blocking","", "Blocking"],["library"," -L/home/greschd/src/ATLAS_3.11/LINUX_13.04/lib/ -lf77blas -latlas -lgfortran","Fortran library"]]

    variables = []
    
    for i in range(2, 11):
        num = 2**i
        iterations = 2**(30 - 3 * i)
        variables.append([num, iterations])
    
    compiler = "g++"
    flags = " -std=c++11 -Wall -O3 -funroll-loops -ftemplate-depth=1500"
    
    
    for f in versions:
        print(f[2] + ":" )
        for v in variables:
            cmd = compiler + flags + " ../main/" + f[0] + ".cpp -o" + f[0] + ".x" + " -DN=" + str(v[0]) + " -DITER=" + str(v[1]) + f[1]
            # for the blocking version, append the right R
            if(f[0] == "blocking"):
                for o in optima:
                    if o[0] == v[0]:
                        cmd += o[1]
            err = os.system(cmd)
            if err != 0:
                print err
            print subprocess.check_output("./" + f[0] + ".x")
    
        

if __name__ == "__main__":
    print("benchmark.py")
   
