import numpy as np
import matplotlib.pyplot as plt
import pylab

def plot(name):
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
    
for i in range(1, 17):
    plot(str(i))
