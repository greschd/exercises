// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    01.10.2014 15:44:54 CEST
// File:    riemann_threads.cpp

#include <cmath>
#include <mutex>
#include <chrono>
#include <thread>
#include <vector>
#include <utility>
#include <iostream>

typedef int count_t;
typedef double res_t;

void riemann_thread(    std::pair<res_t, std::mutex>& result, 
                        res_t const & a,
                        res_t const & b,
                        count_t const & N,
                        std::function<res_t(res_t)> const & f) {
    
    double step = (b - a) / N;
    double x = a + 0.5 * step;
    double sum = 0;
    for(int i = 0; i < N; ++i) {
        sum += f(x);
        x += step;
    }
    
    std::lock_guard<std::mutex> l (result.second);
    result.first += sum * step;
}

res_t riemann_sum(  res_t const & a, 
                    res_t const & b, 
                    count_t const & num_threads, 
                    count_t const & N_per_thread) {
    res_t step = (b - a)/num_threads;
    res_t a1 = a;
    res_t a2 = a + step;
    
    std::pair<res_t, std::mutex> result;
    result.first = 0;
    
    std::function<res_t(res_t)> f = [](double x){return std::sqrt(x)*std::log(x);};
    
    // spawn threads
    std::vector<std::thread> threads(num_threads - 1);
    for(int i = 0; i < num_threads - 1; ++i) {
        threads[i] = std::thread(riemann_thread, std::ref(result), a1, a2, N_per_thread, f);
        a1 += step;
        a2 += step;
    }
    
    // use main thread
    riemann_thread(std::ref(result), a1, a2, N_per_thread, f);
    
    //join threads
    for(std::thread& t : threads) {
        t.join();
    }
    
    return result.first;
}

int main(int argc, char* argv[]) {
    res_t a = 1;
    res_t b = 4;
    
    count_t num_threads = atoi(argv[1]);
    count_t N_per_thread = atoi(argv[2]); 
    
    res_t result = 0;
    // number of repetitions
    count_t runs = 100000;
    
    // create clock
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    // start clock
    start = std::chrono::high_resolution_clock::now();
    // call to riemann
    for(count_t i = 0; i < runs; ++i) {
        result += riemann_sum(a, b, num_threads, N_per_thread);
    }
    // end clock
    end = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double>(end - start).count();
    
    std::cout << "threads: " << num_threads << ", steps: " << N_per_thread * num_threads << ", runs: " << runs <<  ", result: " << result / runs << std::endl;
    std::cout << "elapsed time: " << elapsed_time << "s" << std::endl;
    
    return 0;
}
