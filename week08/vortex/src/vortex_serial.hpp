// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    17.11.2014 11:37:42 CET
// File:    vortex_serial.hpp

#ifndef __VORTEX_SERIAL_HEADER
#define __VORTEX_SERIAL_HEADER

#include "common.hpp"

#include <vector>
#include <iostream>
#include <functional>

class VortexSheet_S {
public:
    // gamma_fct is the gamma(x) from eq. (10)
    VortexSheet_S(  count_t const & N,
                    std::function<val_t(val_t const &)> gamma_fct):
                        particles_(N), particles2_(N) {
        val_t h = 1 / val_t(N);
        val_t x = -0.5 + (0.5 * h);
        for(auto & p: particles_) {
            p.x = x;
            p.y = 0;
            p.gamma = h * gamma_fct(x);
            x += h;
        }
        for(count_t i = 0; i < particles_.size(); ++i) {
            particles2_[i] = particles_[i];
        }
    }

    void print() const {
        std::cout << "x, y, gamma" << std::endl;
        for(auto p: particles_) {
            std::cout << p.x << ", " << p.y << ", " << p.gamma << std::endl;
        }
    }

    void iterate(count_t const & steps, val_t const & dt) {
        for(count_t i = 0; i < steps; ++i) {
            for(count_t j = 0; j < particles_.size(); ++j) {
                complex_t sum(0);
                for(auto & q: particles_) {
                    if(&particles_[j] != &q) {
                        sum += q.gamma / (particles_[j].pos() - q.pos());
                    }
                    particles2_[j].pos(particles_[j].pos() - (complex_t(0, dt)/(2 * pi)) * sum);
                }
            }
            std::swap(particles_, particles2_);
        }
    }
    
private:
    std::vector<Particle> particles_;
    std::vector<Particle> particles2_;
};

#endif //__VORTEX_SERIAL_HEADER
