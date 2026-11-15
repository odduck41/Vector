#pragma once
#include <iostream>

namespace bns { // bns = the best namespace
    template <class T = int>
    class vector {
    public:
        vector() = default;

        vector(const vector&);
        vector& operator=(const vector&);
        friend std::ostream& operator<<(std::ostream&, const vector&);

        void push_back(const T&);
        void pop_back();

        T& operator[](const std::size_t&);
        const T& operator[](const std::size_t&) const;

        [[nodiscard]] std::size_t size() const {
            return size_;
        }

        [[nodiscard]] std::size_t capacity() const {
            return capacity_;
        }

        ~vector() {
            delete[] data_;
        }
    private:
        T* data_{};
        std::size_t size_{};
        std::size_t capacity_{};
    };
}