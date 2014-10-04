// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    03.10.2014 11:09:05 CEST
// File:    barrier.hpp

#include <mutex>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>

namespace barrier{
    typedef int count_t;

    class barrier_cl {
    public:
        barrier_cl(count_t const & num_threads):   num_threads_(num_threads), 
                                                counter_(0)
                                                {};
                                                
        void wait() {
            std::unique_lock<std::mutex> l(counter_mutex_);
            // need two "levels" s.t. threads already in the next wait()
            // function don't block current thread by changing counter_
            bool second = (counter_ >= num_threads_);
            ++counter_;
            if(counter_ == 2 * num_threads_) {
                counter_ = 0;
            }
            l.unlock();
            // access only, no need to lock
            if(second) {
                while(counter_ > num_threads_) {
                }
            }
            else {
                while(counter_ < num_threads_){}
            }
        }
        
    private:
        const count_t num_threads_;
        count_t counter_;
        std::mutex counter_mutex_;
    };
}
