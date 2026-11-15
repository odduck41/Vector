#pragma once
#include <iostream>
#include "vector.hpp"

namespace bns {
    template <class T>
    class Stack {
    public:
        Stack() = default;

        Stack(const Stack& other);
        Stack& operator=(const Stack&);

        friend std::ofstream& operator<< (std::ofstream&, Stack<T>);

        void push(const T&);
        T& top();
        T& top() const;
        void pop();

        ~Stack();
    private:
        T* data_{};
        std::size_t size_{};
    };
}