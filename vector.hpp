#pragma once
#include <iostream>

namespace bns { // bns = the best namespace
    template <class T = int>
    class vector {
    public:
        vector() = default;

        vector(const vector& other) : size_(other.size_), capacity_(other.capacity_) {
            if (this->data_ == other.data_) return;

            delete[] this->data_;
            this->size_ = other.size_;
            this->capacity_ = other.capacity_;
            this->data_ = new T[this->capacity_];

            std::copy(other.data_, other.data_ + this->size_, this->data_);
        }

        vector& operator=(const vector& other) {
            if (this == &other) return *this;

            delete[] this->data_;
            this->size_ = other.size_;
            this->capacity_ = other.capacity_;
            this->data_ = new T[this->capacity_];

            std::copy(other.data_, other.data_ + this->size_, this->data_);
            return *this;
        }

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