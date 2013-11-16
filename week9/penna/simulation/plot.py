import numpy as np
import matplotlib.pyplot as plt
import pylab

def plot_sizes():
    #----------------------- input ----------------------- 
    ios1 = open("../build/m_0.txt", 'r')
    data1 = np.loadtxt(ios1, skiprows = 1)
    ios1.close()
    
    ios2 = open("../build/m_8.txt", 'r')
    data2 = np.loadtxt(ios2, skiprows = 1)
    ios2.close();
    
    #------------------------ plot ----------------------- 
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
    
def plot_ageatdeath():
    #----------------------- input ----------------------- 
    ios = open("../build/m_ageatdeath.txt")
    data = np.loadtxt(ios, skiprows = 1)
    ios.close()
    
    #------------------------ plot ----------------------- 
    fig, ax1 = plt.subplots()
    plt.title("M = 2, T = 4")
    plt.grid(True)
    plt.xlabel("R")
    ax1.set_ylabel("Age at Death (red)")
    ax1.plot(data[:,0], data[:,1], 'rs')
    ax2 = ax1.twinx()
    ax2.set_ylabel("Population Size (blue)")
    ax2.plot(data[:,0], data[:,2],'bo')
    
    #------------------- save the plot ------------------- 
    pylab.savefig("../build/age_at_death.pdf")
    plt.clf()
    
def plot_genedistr():
    #----------------------- input ----------------------- 
    ios = open("../build/m_genedistr.txt")
    data = np.loadtxt(ios, skiprows = 1)
    ios.close()
    
    #------------------------ plot ----------------------- 
    plt.title("M = 8, T = 2, R = 8")
    plt.grid(True)
    plt.xlabel("Gene position")
    plt.ylabel("number of bad genes")
    plt.bar(data[:,0], data[:,1])
    
    #------------------- save the plot ------------------- 
    pylab.savefig("../build/gene_distr.pdf")
    plt.clf()

plot_sizes()
#~ plot_ageatdeath()    
#~ plot_genedistr()
