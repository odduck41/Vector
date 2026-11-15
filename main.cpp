//
// Created by Lev Dymchenko on 15.11.2026.
//

#include "vector.hpp"

int main() {
    bns::vector<bns::vector<int>> a;
    bns::vector<int> b;
    b.push_back(1);
    a.push_back(b);
    b.pop_back();
    b.push_back(2);
    a.push_back(b);
    std::cout << a;
    return 0;
}