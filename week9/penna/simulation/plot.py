import numpy as np
import matplotlib.pyplot as plt
import pylab

def plot_sizes():
    ios0 = open("../build/m_0.txt", 'r')
    data0 = np.loadtxt(ios0, skiprows = 1)
    ios0.close()
    
    ios2 = open("../build/m_2.txt", 'r')
    data2 = np.loadtxt(ios2, skiprows = 1)
    ios2.close();
    
    
    plt.title("Population size for T = 2, R = 8, starting with 450'000 animals.")
    plt.grid(True)
    plt.xlabel("years")
    plt.ylabel("population size")
    plt.xscale('log')
    plt.yscale('log')
    plt.plot(data0[:,0], data0[:,1],'ro', label = "m = 0")
    plt.plot(data2[:,0], data2[:,1],'go', label = "m = 2")
    plt.legend(bbox_to_anchor = (1, .3), loc = 5)

    #------------------- save the plot ------------------- 
    pylab.savefig("../build/population_size.pdf")
    plt.clf()
    
plot_sizes()
