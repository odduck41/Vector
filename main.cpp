#include <vector>
#include "Vector.h"
#include <iostream>

using namespace std;

int main() {
    Vector<int> a(3);
    a[0] = 41;
    a[1] = 42;
    a[2] = 67;
    for (auto& i: a) {
        cout << i << " ";
    }
}