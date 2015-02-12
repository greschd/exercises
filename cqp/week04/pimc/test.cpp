// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    13.03.2014 15:15:42 CET
// File:    test.cpp

#include <iostream>
#include <functional>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> v({std::vector<int>({1,2,3})});
    v.push_back(std::vector<int>({4, 5, 6}));
    std::cout << v.at(1).at(1) << std::endl;
    return 0;
}
