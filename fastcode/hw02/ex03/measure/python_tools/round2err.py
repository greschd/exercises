#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    12.03.2014 19:29:19 CET
# File:    round2err.py

import sys
import numpy as np
from math import log10, floor
    
# rounding a value to its error, the error to 1 significant digit
def rnd2err(val, err, string = True):
    # catch division by 0
    if(err == 0):
        return[val, err]
    else:
        val = round(val, int(floor(1 - log10(err))))
        err = round(err, int(floor(1 - log10(err))))
    if(not(string)):
        return [val, err]
    else:
        return r"$" + str(val).strip('0').rstrip('.') + r"~\pm~" + str(err).strip('0').rstrip('.') + r"$"

def rnd2errlist(data, string = True):
    res = []
    for d in data:
        res.append(rnd2err(d[0],d[1]))
    return res
    
def avg_err(A):
    n = len(A)
    if(n < 2):
        return A
    else:
        avg = sum(A) / n
        err = np.sqrt(sum((a - avg)**2 for a in A)/(n - 1))
        return [avg, err]
