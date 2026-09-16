#include "vector.h"

template<class T>
Vector<T>::Vector(const std::size_t& sz, const T& val) :
array_(new T[sz]), size_(sz), capacity_(sz) {
    for (std::size_t _ = 0; _ < size_; ++_) {
        array_[_] = val;
    }
}

template<class T>
Vector<T>::Vector(const std::size_t & sz) :
array_(new T[sz]), size_(sz), capacity_(sz) {}

template<class T>
Vector<T>::Vector(const std::initializer_list<T> & list) :
array_(new T[list.size()]), size_(list.size()), capacity_(list.size()) {
    for (std::size_t _ = 0; _ < this->size_; ++_) {
        array_[_] = list[_];
    }
}

template<class T>
Vector<T>::Vector(const Vector & other) {
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;
    array_ = new T[this->size_];
    for (std::size_t _ = 0; _ < this->size_; ++_) {
        this->array_[_] = other.array_[_];
    }
}

template<class T>
Vector<T>::Vector(Vector && other) noexcept :
array_(nullptr), size_(0), capacity_(0) {
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->array_, other.array_);
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector & other) {
    delete[] array_;
    this->Vector(other);
    return *this;
}

template<class T>
Vector<T> & Vector<T>::operator=(Vector && other) noexcept {
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->array_, other.array_);

    return *this;
}

template<class T>
Vector<T> & Vector<T>::operator=(const std::initializer_list<T>& list) {
    delete[] this->array_;
    this->Vector(list);
    return *this;
}

template<class T>
Vector<T>::~Vector() {
    delete[] array_;
    size_ = 0;
    capacity_ = 0;
}
