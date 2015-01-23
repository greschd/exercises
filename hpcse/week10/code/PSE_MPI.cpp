#include <mpi.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

class PSE2D
{
private:
    const int support[2] = {-10,11};
    const double eps;
    
public:
    PSE2D(int N) : eps(2./N) {}
    
    inline const int getStart() const
    {
        return support[0];
    }
    
    inline const int getEnd() const
    {
        return support[1];
    }
    
    inline const double w(double dx, double dy) const
    {
        // TODO: fill here (PSE kernel evaluation)
    }
};


template<class Kernel>
class DiffusionPSE
{
private:
    // data structures for position (x) and concentrations (c)
    // these array contain ghosts in addition to the domain of each rank
    vector<double> cPing, cPong;
    
    // PSE kernel
    Kernel k;
    
    // Grid spacing, problem size
    double dh;
    const int N;
    
    // MPI stuff
    int rank, size, Mx, My;
    
    // MPI communication buffers
    // TODO: fill here
    
    double analytical(double x, double y, double t)
    {
        return sin(2.*M_PI*x)*sin(2.*M_PI*y)*exp(-8*M_PI*t);
    }
    
public:
    DiffusionPSE(int rank, int size, int N, int Mx, int My) : rank(rank), size(size), dh(1./(double)N), k(N), N(N), Mx(Mx), My(My)
    {
        if (N % Mx != 0)
        {
            if (rank==0) cout << "Problem size is not divisible by number of ranks in x-direction!\nAborting now...\n";
            abort();
        }
        if (N % My != 0)
        {
          if (rank==0) cout << "Problem size is not divisible by number of ranks in y-direction!\nAborting now...\n";
          abort();
        }
      
        // TODO: fill here
    }
    
    ~DiffusionPSE()
    {
        // TODO: fill here
    }
    
    void setIC()
    {
        // TODO: fill here
    }
    
    void simulate()
    {
        // time loop
        const int nsteps = 100;
        const int supportSize = -k.getStart();
        for (int t=0; t<nsteps; t++)
        {
            // TODO: fill here
            
            // swap the two data structures s.t. the current solution is always in cPing
            cPing.swap(cPong);
        }
    }
};

int main(int argc, char *argv[])
{
    //=========================
    //      Initialize MPI
    //=========================
    MPI_Init(&argc, &argv);
    
    // set MPI configuration
    Mx = 2;
    My = 2;
  
    //=========================
    //      get rank information
    //      (processID and #processes)
    //=========================
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != Mx*My)
    {
        if (rank==0) cout << "Inconsistent number of MPI Processes\n";
        abort();
    }
    printf("Hello from process %d of %d\n", rank, size);
    
    // Problem size
    int N = 120;
    
    // setup simulation
    DiffusionPSE<PSE2D> diffusion(rank,size,N,Mx,My);
    diffusion.setIC();
    
    // run simulation
    diffusion.simulate();
    
    
    //=========================
    //      cleanup MPI environment
    //=========================
    MPI_Finalize();
    
    return 0;
}