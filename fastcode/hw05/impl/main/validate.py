#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    01.04.2014 17:55:48 CEST
# File:    validate.py

import sys
import os

sizes = [8, 16, 24, 56, 256]
versions = ["0", "1", "2", "3"]
    
def compile_verify():
    cmd1 = "g++ -std=c++11 "
    for v in versions:
        for N in sizes:
            cmd2 = "-DNB=" + str(N)
            cmd3=  " -o " + v + "_" + str(N) + ".out" + " ../validate/verify_" + v + ".cpp"
            os.system(cmd1 + cmd2 + cmd3)

def run_verify():
    for v in versions:
        for N in sizes:
            cmd = "./" + v + "_" + str(N) + ".out"
            os.system(cmd)
            
sizes2 = [i * 86 for i in range(1,5)]
print(sizes2)
def compile_verify_final():
    cmd1 = "g++ -std=c++11 "
    for N in sizes2:
        cmd2 = "-DN=" + str(N)
        cmd3=  " -o final_" + str(N) + ".out" + " ../validate/verify_final.cpp"
        os.system(cmd1 + cmd2 + cmd3)

def run_verify_final():
    for N in sizes2:
        cmd = "./final_" + str(N) + ".out"
        os.system(cmd)


#~ compile_verify()
#~ run_verify()
compile_verify_final()
run_verify_final()
print("tested successfully")
