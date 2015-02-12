#!/usr/bin/python3.2
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    10.03.2014 09:25:49 CET
# File:    list2tex.py

import sys

def p2t(data, name = "table", environment = "tabular", align = "l", specialformat = "none", specialhlines = {}, leftline = True, rightline = True, topline = True, bottomline = True, hlines = 1):

    m = len(data)
    n = len(data[0]) 
    
# beginning: setting up the environment
    envopen = r"\begin{" +str(environment) + r"}  {"
    if(specialformat == "none"):
        if(leftline):
            envopen += r"|"
        for i in range(n - 1):
            envopen += align + r"|"
        envopen += align
        if(rightline):
            envopen += r"|"
        envopen += "}\n\t"
    else:
        envopen += specialformat + r"}\n\t"

# data
    for i in range(m - 1):
        specialhlines.setdefault(i, hlines)
    specialhlines.setdefault(m - 1, hlines - 1)
    table = ""
    if(topline):
        table += r"\firsthline" + "\n\t"
    for i in range(m):
        for j in range(n - 1):
            table += str(data[i][j]) + r" & "
        table += str(data[i][n - 1]) + r"\\"
        for k in range(specialhlines[i]):
            table += r"\hline"
        table += "\n\t"
    if(bottomline):
        table += r"\lasthline"
    table += "\n"
    
# closing the environment
    envclose = r"\end{" + environment + "}"
    
# putting it together
    table = envopen + table + envclose

# writing it to the file
    w = open(name + ".tex", "w")
    w.write(table)
    w.close()
    
if __name__ == "__main__":
    test()
    print("list2tex.py")
    
