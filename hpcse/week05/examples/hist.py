#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@gmx.ch>
# Date:    29.10.2014 16:52:51 CET
# File:    hist.py

import sys
sys.path.append("../python_tools")
from plot_setup import *

import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    name = sys.argv[1].split('.txt')[0]
    with open(name + ".txt", "r") as f:
        res = np.array(eval(f.read()))

    plt.bar(range(512), res[:,0])
    plt.xlim(0, 512)
    plt.savefig('res/hist_' + name.split('/')[-1] + ".pdf", bbox_inches='tight')
    

    print("plot.py")
