#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    17.11.2014 17:54:14 CET
# File:    run.py

nproc = [1, 2, 4, 6, 8]
nproc.extend(list(range(12, 49, 4)))
with open("run.sh", "w") as f:
    for i in nproc:
        f.write("mpiexec -n " + str(i) + " ./a.out 10000 50 > t_" + str(i) + ".txt;\n")

