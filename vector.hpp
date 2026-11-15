#pragma once
#include <iostream>

namespace bns { // bns = the best namespace
    template <class T = int>
    class vector {
    public:
        vector();
        ~vector();
        vector(const vector&);
        vector& operator=(const vector&);
        friend std::ostream& operator<<(std::ostream&, const vector&);

        void push_back(const T&);
        void pop_back();

        T& operator[](const std::size_t&);

    private:
    };
}