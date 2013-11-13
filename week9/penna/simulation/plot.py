import numpy as np
import matplotlib.pyplot as plt
import pylab

def plot_size(name):
    ios = open("../build/m_" + name + ".txt", 'r')
    data = np.loadtxt(ios, skiprows = 1)
    ios.close()
    
    ios = open("../build/v_" + name + ".txt", 'r')
    var = np.loadtxt(ios, skiprows = 1)

    title = "m0 = " + str(var[0]) + ", m = " + str(var[1]) + ", nmax = " + str(var[2]) + ", n0 = " + str(var[3]) + ", T = " + str(var[4]) + ", R = " + str(var[5])
    plt.title(title)
    plt.grid(True)
    plt.xlabel("years")
    plt.ylabel("population size")
    plt.plot(data[:,0], data[:,1],'ro')

    #------------------- save the plot ------------------- 
    pylab.savefig("../build/p_" + name + ".pdf")
    plt.clf()
    
def plot_ageofdeath(): 
    ios = open("../build/age_of_death.txt")
    data = np.loadtxt(ios, skiprows = 1)
    ios.close()
    
    plt.title("Average age of death with varying mutation rate")
    plt.grid(True)
    plt.xlabel("mutation rate")
    plt.ylabel("average age of death")
    plt.plot(data[:,0], data[:,1], 'go')
    
        #------------------- save the plot ------------------- 
    pylab.savefig("../build/age_of_death.pdf")
    plt.clf()
    
def plot_genedistribution():
    ios = open("../build/initial.txt")
    initial = np.loadtxt(ios, skiprows = 1)
    ios.close()
    
    ios2 = open("../build/final.txt")
    final = np.loadtxt(ios2, skiprows = 1)
    ios2.close()
    
    plt.title("Gene distribution in the initial population")
    plt.grid(True)
    plt.xlabel("threshold")
    plt.ylabel("survivors")
    plt.plot(initial[:,0], initial[:,1], 'bo')
    
        #------------------- save the plot ------------------- 
    pylab.savefig("../build/initial.pdf")
    plt.clf()
    
    plt.title("Gene distribution in the final population")
    plt.grid(True)
    plt.xlabel("threshold")
    plt.ylabel("survivors")
    plt.plot(final[:,0], final[:,1], 'bo')
    
        #------------------- save the plot ------------------- 
    pylab.savefig("../build/final.pdf")
    plt.clf()
    
    
    
for i in range(1, 21):
    plot_size(str(i))
plot_ageofdeath()
plot_genedistribution()
