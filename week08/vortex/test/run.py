#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    17.11.2014 17:54:14 CET
# File:    run.py

nproc = [1, 2, 4, 6, 8]
nproc.extend(list(range(12, 43, 4)))
nproc.append(48)

n = 10080
for i in nproc:
    if(n % i != 0):
        print(str(n) + ' not divisible by ' + i)

with open("run.sh", "w") as f:
    for i in nproc:
        f.write("mpiexec -n " + str(i) + " ./a.out 10080 50 > ../res/strong_" + str(i) + ".txt;\n")
    for i in nproc:
        f.write("mpiexec -n " + str(i) + " ./a.out + " + str(n / i) + " 50 > ./res/weak_" + str(i) + ".txt;\n")

