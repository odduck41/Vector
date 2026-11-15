//
// Created by Lev Dymchenko on 15.11.2026.
//

#include "stack.hpp"

int main() {
    bns::Stack<int> h;
    h.push(1);
    h.pop();
    h.push(2);
    h.push(1);
    h.push(4);
    h.push(10);
    bns::Stack<int> e;
    e.push(1);
    e.push(2);
    std::cout << e << std::endl;
    e = h;
    std::cout << e;
    return 0;
}