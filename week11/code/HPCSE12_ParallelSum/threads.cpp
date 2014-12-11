// Skeleton code for HPCSE Exam, 18.12.2012
// Profs. P. Koumoutsakos and M. Troyer
// Question 5b)

#include <vector>
#include <numeric>
#include <iostream>
#include <thread>

void sum(int rank,
         int size,
         int N,
         std::vector<float>& x,
         std::vector<float>& y,
         std::vector<float>& z) {
    for(int i = rank * N / size; i < (rank + 1) * N / size ; ++i) {
        z[i] = x[i] + y[i];
    }
}

int main( int argc, char** argv )
{
    // vector size
    const int N = 1600000;

    // initialize vectors
    std::vector<float> x(N,-1.2), y(N,3.4), z(N);

    /// no overlapping memory access -> no need for mutices
    // DO THE SUM z = x + y using 4 threads
    std::vector<std::thread> threads(4);
    for(int i = 0; i < 4; ++i) {
        threads[i] = std::thread(sum, i, 4, N, std::ref(x), std::ref(y), std::ref(z));
    }
    for(auto & t: threads) {
        t.join();
    }

    // print result checksum
    std::cout << std::accumulate(z.begin(), z.end(), 0.) << std::endl;
}

