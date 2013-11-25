# Author:  Dominik Gresch <greschd@phys.ethz.ch>
# Date:    11.10.2013 15:37:19 CEST
# File:    plot.py

import sys
import matplotlib #install pylab and matplotlib for python 2.7
matplotlib.use('Agg') #only save /no show / comment to see difference
import pylab

def main():
    ### +---------------------------------------------------+
    ### |                   read the data                   |
    ### +---------------------------------------------------+
    f = open("output-3.txt")
    g = f.readlines() #g[0] is entire first line, g[1] is second line ...
    
    labels = g[0].split() #split splits at whitespace, g[0].split() is a vector with the labels
    
    print(labels) #just to check...
    
    data = [[] for i in range(len(labels))] # is now a list of lists (list == c++::vector), [[], [], [], []]
    
    print(data)
    
    for i in range(1, len(g)): # the first g was the labels
        points = g[i].split()
        for j in range(len(points)):
            data[j].append(points[j]) #append == c++::vector.push_back()
    
    print(data)
    
    ### +---------------------------------------------------+
    ### |                   plot the data                   |
    ### +---------------------------------------------------+
    
    x = 0
    y = 1
    
    print("you plot {0} vs {1}".format(labels[x], labels[y]))
    
    pylab.xlabel(labels[x])
    pylab.ylabel(labels[y])
    pylab.title("Step size = 3")
    pylab.xscale('log')
    
    pylab.grid(True)
    pylab.plot(data[x], data[y])
    #~ pylab.plot(data[x], data[x], marker = ".", linestyle = "-", color = "r") #more options
    
    #------------------- save the plot ------------------- 
    path_img = "plot-3.pdf" #.png works as well
    pylab.savefig(path_img)
    pylab.show() #only works if line 10 is commented
    

if __name__ == "__main__":
    print("minimal_plot.py")
    main();
