// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    24.08.2014 12:01:08 CEST
// File:    Deutsch_Josza.cpp

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>
#include <functional>

class state_cl {
public:
    state_cl(uint const & i, uint const & N): state_(std::vector<double>(1<<N)), num_qubits_(N) {
        state_[1 << i] = 1;
    };
    void Hadamard(uint const & n) {
        double val;
        double prefactor = 1/std::sqrt(2);
        assert(n < state_.size());
        std::vector<double> res(1<<num_qubits_);
        for(uint i = 0; i < state_.size(); ++i) {
            val = prefactor * state_[i];
            res[i ^ (1<<n)] += val;
            if((i & (1<<n)) == 0) {
                res[i] += val;
            }
            else {
                res[i] -= val;
            }
        }
        state_ = res;
    }
    
    void Uf(std::function<int(int const &)> const & f) {
        std::vector<double> res(1<<num_qubits_);
        for(uint i = 0; i < state_.size(); ++i) {
            res[f(i>>1)^i] += state_[i];
        }
        state_ = res;
    }
    
    void print() const {
        double val;
        bool first = true;
        for(uint i = 0; i < state_.size(); ++i) {
            val = state_[i];
            if(val != 0) {
                if(!first && (val > 0)) {
                    std::cout << " +";
                }
                std::cout << " ";
                first = false;
                std::cout << val << " |";
                for(int j = num_qubits_ - 1; j >= 0; --j) {
                    if(((1<<j) & i) != 0) {
                        std::cout << "1";
                    }
                    else {
                        std::cout << "0";
                    }
                }
                std::cout << ">";
            }
        }
        std::cout << std::endl;
    }
    
    double get(int const & i) const {
        return state_[i];
    }
    
private:
    std::vector<double> state_;
    uint num_qubits_;
};

void DJ(uint const & n, std::function<int(int)> f) {
    state_cl state(0,n);
    for(uint i = 0; i < n; ++i) {
        state.Hadamard(i);
    }
    state.Uf(f);
    for(uint i = 0; i < n; ++i) {
        state.Hadamard(i);
    }
    if(fabs(state.get(0)) + fabs(state.get(1)) > 0.5) {
        std::cout << "f is constant" << std::endl;
    }
    else {
        std::cout << "f is balanced" << std::endl;
    }
    state.print();
}


int main(int argc, char* argv[]) {
    int n;
    std::cout << "n = ?" << std::endl;
    std::cin >> n;
    DJ(n, [](int a){return (a%2==0)?0:1;});
    DJ(n, [](int a){return 1;});
}
