// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    06.11.2013 16:41:45 CET
// File:    z2.cpp

#include <iostream>

// Z2 class
enum Z2 {Plus, Minus};

template<class T> /// needs to have a copy constructor that accepts 1 as an argument
T identity_element() { return T(1); }

template<>
Z2 identity_element() {return Plus;}

Z2 operator*(const Z2 a,const Z2 b) {
    return (a == b ? Plus : Minus);
}

std::ostream& operator<<(std::ostream& os,const Z2 a) {
    os << (a == Plus ? "Plus" : "Minus");
    return os;
}

template<class T> /// needs: comparison, unitary minus
T operator*(const T a, const Z2 b)
{
    return (b == Plus ? a : -a);
}

template<class T> /// needs: comparison, unitary minus
T operator*(const Z2 b, const T a)
{
    return (b == Plus ? a : -a);
}

template<class T> /// needs: assignability, multiplication (plus the conditions from identity_element)
T mypow(T a, const unsigned int n)
{
    T b = identity_element<T>();
    for(unsigned int i = 0; i < n; ++i) {
        b = b * a;
    }
    return b;
}

int main()
{
  // some testing: feel free to add your own!
  std::cout << Plus*Minus << std::endl;
  std::cout << Plus*-1*Minus << std::endl;
  std::cout << identity_element<Z2>() << std::endl; /// test identity_element()
  std::cout << (1.+3.)*mypow(Minus,4) << std::endl;
  for (unsigned i=0; i<7; i++)
    std::cout << "Plus^" << i << " = " << mypow(Plus,i) << std::endl;
  for (unsigned i=0; i<7; i++)
    std::cout << "Minus^" << i << " = " << mypow(Minus,i) << std::endl;
  for (unsigned i=0; i<7; i++)
    std::cout << "2^" << i << " = " << mypow(2.0,i) << std::endl;
  return 0;
}
