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

        void push_back(const T& element) {
            if (size_ + 1 >= capacity_) { // size + 1 < capacity
                (++capacity_) <<= 1;
            }
            data_[size_] = element;
            ++size_;
        }
        void pop_back() {
            if (size_ == 0) ; // TODO: add exception(!)
            if (size_ > 0) --size_;
            if ((size_ + size_ / 2 + 1) * 2 <= capacity_) {
                capacity_ = size_ + size_ / 2 + 2;
                auto new_data = new T[capacity_];
                std::copy(data_, data_ + size_, new_data);
                delete data_[];
                data_ = new_data;
            }
        }

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