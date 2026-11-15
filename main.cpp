//
// Created by Lev Dymchenko on 15.11.2026.
//

#include "stack.hpp"
#include "vector.hpp"

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
    std::cout << e << std::endl;
    e.pop();
    e.pop();
    e.pop();
    e.pop();
    try {
        e.pop();
    } catch (bns::Empty& err) {
        std::cout << err.what();
    }
    return 0;
}