// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    28.02.2014 18:04:29 CET
// File:    framework.cpp

#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <cmath>

typedef double val_t;
typedef unsigned int index_t;

// Komplexe Zahlen
class complex_cl {
public:
    complex_cl(val_t r = 0, val_t i = 0): Re_(r), Im_(i) {};
    
    complex_cl const & operator=(val_t const & x) {
        Re_ = x;
        Im_ = 0;
        return *this;
    }
    
    complex_cl const & operator+=(complex_cl const & y) {
        Re_ += y.Re_;
        Im_ += y.Im_;
        return *this;
    }
    
    complex_cl const & operator*=(complex_cl const & y) {
        val_t r = Re_;
        Re_ = Re_ * y.Re_ - Im_ * y.Im_;
        Im_ = r * y.Im_ + Im_ * y.Re_;
        return *this;
    }
    
    complex_cl const & operator*=(val_t const & a) {
        Re_ = a * Re_;
        Im_ = a * Im_;
        return *this;
    }
    
    val_t re() const {
        return Re_;
    }
    
    val_t im() const {
        return Im_;
    }
    
    void set_re(val_t const & r) {
        Re_ = r;
    }
    
    void set_Im(val_t const & i) {
        Im_ = i;
    }
    
    complex_cl conj() const{
        return complex_cl(Re_, -Im_);
    }
    
private:
    val_t Re_;
    val_t Im_;
};

bool operator==(complex_cl const & x, complex_cl const & y) {
    return (x.re() == y.re()) && (x.im() == y.im());
}

bool operator!=(complex_cl const & x, complex_cl const & y) {
    return !(x==y);
}

complex_cl operator+(complex_cl x, complex_cl const & y) {
    return x += y;
}

complex_cl operator*(complex_cl  x, complex_cl const & y) {
    return x *= y;
}

complex_cl operator*(val_t const & a, complex_cl  x) {
    return x *= a;
}

complex_cl operator*(complex_cl x, val_t const & a) {
    return x *= a;
}

std::ostream& operator<<(std::ostream & os, complex_cl const & c) {
    if(c.im() == 0) {
        os << c.re();
    }
    else if (c.re() == 0) {
        os << c.im() << " i";
    }
    else {
        os << c.re() << " + " << c.im() << " i";
    }
    return os;
}
//-------------------------------------------//

typedef std::vector<complex_cl> vec_t;

// Wellenfunktion in der Besetzungszahlbasis
class wfct_cl {
public:
    wfct_cl(index_t const & n = 0, complex_cl const & c = 1) {
        vec_t wfct(n);
        wfct.push_back(c);
        wfct_ = wfct;
    } 
    
    wfct_cl(vec_t const & wfct): wfct_(wfct) {};
    
    wfct_cl const & operator+=(wfct_cl const & psi) {
        wfct_.resize(std::max(psi.size(), this -> size()));
        for(index_t i = 0; i < psi.size(); ++i) {
            wfct_.at(i) += psi.get(i);
        }
        return *this;
    }
    
    wfct_cl const & operator*=(complex_cl const & c) {
        for(index_t i = 0; i < wfct_.size(); ++i) {
            wfct_.at(i) *= c;
        }
        return *this;
    }
    
    complex_cl get(index_t const & n) const {
        return wfct_.at(n);
    }
    
    void set(index_t const & n, complex_cl const & c) {
        // no extra zeroes at the end
        if(n == wfct_.size() - 1 && c == complex_cl(0,0)) {
            wfct_.pop_back();
        }
        else {
            wfct_.at(n) = c;
        }
    }
    
    // return adagger * wfct
    wfct_cl rise() const{
        wfct_cl temp(wfct_);
        return temp.rise_modify();
    }
    
    // turns wfct into adagger * wfct
    wfct_cl const & rise_modify() {
        wfct_.insert(wfct_.begin(), 0);
        for(index_t i = 0; i < wfct_.size(); ++i) {
            wfct_.at(i) *= std::sqrt(i);
        }
        return *this;
    }
    
    // return a * wfct
    wfct_cl fall() const {
        wfct_cl temp(wfct_);
        return temp.fall_modify();
    }
    
    // turns wfct into a * wfct
    wfct_cl const & fall_modify() {
        wfct_.erase(wfct_.begin());
        for(index_t i = 0; i < wfct_.size(); ++i) {
            wfct_.at(i) *= std::sqrt(i + 1);
        }
        return *this;
    }
    
    index_t size() const {
        return wfct_.size();
    }
    
    
private:
    vec_t wfct_;
};

// <psi|phi>
complex_cl prod(wfct_cl const & psi, wfct_cl const & phi) {
    complex_cl res = 0;
    for(index_t i = 0; i < std::min(psi.size(), phi.size()); ++i) {
        res += psi.get(i).conj() * phi.get(i);
    }
    return res;
}

std::ostream& operator<< (std::ostream & os, wfct_cl psi) {
    for(index_t i = 0; i < psi.size() - 1; ++i) {
        if(psi.get(i) != complex_cl(0,0)) {
            os << "(" <<  psi.get(i) << ") * |" << i << "> + ";
        }
    }
    os << "(" <<  psi.get(psi.size() - 1) << ") * |" << psi.size() - 1 << ">";
    return os;
}

wfct_cl operator*(complex_cl const & c, wfct_cl psi) {
    return psi *= c;
}

wfct_cl operator+(wfct_cl psi, wfct_cl const & phi) {
    return psi += phi;
}
//-------------------------------------------//

class op_cl {
public:
    op_cl(): op_([](wfct_cl const & x){return x;}) {};
    
    op_cl(std::function<wfct_cl(wfct_cl const &)> op): op_(op) {};
    
    enum stdop {id, a, adagger};
    
    op_cl(stdop const & o) {
        if(o == a) {
            op_ = [](wfct_cl const & psi){return psi.fall();};
        }
        else if(o == adagger)
            op_ = [](wfct_cl const & psi){return psi.rise();};
        else 
            op_ = [](wfct_cl const & psi){return psi;};
    }
    
    op_cl const & operator=(op_cl const & o) {
        op_ = o.op_;
        return *this;
    }
    
    op_cl const & operator=(std::function<wfct_cl(wfct_cl const &)> const & o) {
        op_ = o;
        return *this;
    }
    
    wfct_cl operator()(wfct_cl const & psi) const{
        return op_(psi);
    }
    
    op_cl const & operator+=(op_cl const & A) {
        auto f = op_;
        op_ = [f, A](wfct_cl const & psi){return f(psi) + A(psi);};
        return *this;
    }
    
    op_cl const & operator*=(op_cl const & A) {
        auto f = op_;
        op_ = [f, A](wfct_cl const & psi){return f(A.op_(psi));};
        return *this;
    }
    
    op_cl const & operator*=(complex_cl const & c) {
        auto f = op_;
        op_ = [f, c](wfct_cl const & psi){return c * f(psi);};
        return *this;
    }
    
private:
    std::function<wfct_cl(wfct_cl const &)> op_;
};

op_cl operator+(op_cl A, op_cl const & B) {
    return A += B;
}

op_cl operator*(op_cl A, op_cl const & B) {
    return A *= B;
}

op_cl operator*(complex_cl const & c, op_cl A) {
    return A *= c;
}
