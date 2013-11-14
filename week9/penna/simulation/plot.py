import numpy as np
import matplotlib.pyplot as plt
import pylab

def plot_sizes():
    ios1 = open("../build/m_0.txt", 'r')
    data1 = np.loadtxt(ios1, skiprows = 1)
    ios1.close()
    
    ios2 = open("../build/m_8.txt", 'r')
    data2 = np.loadtxt(ios2, skiprows = 1)
    ios2.close();
    
    
    plt.title("T = 2, R = 8, Nmax = 10000, N0 = 9000")
    plt.grid(True)
    plt.xlabel("years")
    plt.ylabel("population size")
    plt.xscale('log')
    plt.yscale('log')
    plt.plot(data1[:,0], data1[:,1],'r+', label = "m = 0")
    plt.plot(data2[:,0], data2[:,1],'g.', label = "m = 8")
    plt.legend(bbox_to_anchor = (1, .3), loc = 5)

    #------------------- save the plot ------------------- 
    pylab.savefig("../build/population_size.pdf")
    plt.clf()
    
plot_sizes()
