#include "Vector.h"

#ifndef vector_cpp
#define vector_cpp

template<class T>
Vector<T>::Vector(const std::size_t& sz, const T& val) :
data_(new T[sz + 1]), size_(sz), capacity_(sz + 1) {
    for (std::size_t _ = 0; _ < size_; ++_) {
        data_[_] = val;
    }
}

template<class T>
Vector<T>::Vector(const std::size_t & sz) :
data_(new T[sz + 1]), size_(sz), capacity_(sz + 1) {}

template<class T>
Vector<T>::Vector(const std::initializer_list<T> & list) :
data_(new T[list.size()]), size_(list.size()), capacity_(list.size() + 1) {
    for (std::size_t _ = 0; _ < this->size_; ++_) {
        data_[_] = list[_];
    }
}

template<class T>
Vector<T>::Vector(const Vector & other) :
size_(other.size_), capacity_(other.capacity_) {
    data_ = new T[this->capacity_];
    for (std::size_t _ = 0; _ < this->size_; ++_) {
        this->data_[_] = other.data_[_];
    }
}

template<class T>
Vector<T>::Vector(Vector && other) noexcept :
data_(nullptr), size_(0), capacity_(0) {
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->data_, other.data_);
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector & other) {
    if (other == *this) {
        return *this;
    }

    delete[] data_;
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;

    data_ = new T[this->capacity_];

    for (std::size_t _ = 0; _ < this->size_; ++_) {
        this->data_[_] = other.data_[_];
    }
    return *this;
}

template<class T>
Vector<T> & Vector<T>::operator=(Vector && other) noexcept {
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->data_, other.data_);

    return *this;
}

template<class T>
Vector<T> & Vector<T>::operator=(const std::initializer_list<T>& list) {
    this->size_ = list.size();
    this->capacity_ = list.size() + 1;
    delete[] this->data_;
    this->data_ = new T[this->capacity_];
    for (std::size_t _ = 0; _ < this->size_; ++_) {
        data_[_] = list[_];
    }
    return *this;
}

template<class T>
Vector<T>::~Vector() {
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
}

template<class T>
void Vector<T>::push_back(const T & val) {
    ++size_;
    if (size_ + 1 >= capacity_) {
        capacity_ *= 2;
        realloc(capacity_);
    }
    data_[size_ - 1] = val;
}

template<class T>
void Vector<T>::pop_back() {
    --size_;
}

template<class T>
void Vector<T>::emplace_back(T && val) {
    ++size_;
    if (size_ + 1 >= capacity_) {
        capacity_ *= 2;
        realloc(capacity_);
    }

    std::swap(data_[size_ - 1], val);
}

template<class T>
T & Vector<T>::operator[](const std::size_t & index) {
    return data_[index];
}

template<class T>
const T & Vector<T>::operator[](const std::size_t & index) const {
    return data_[index];
}

template<class T>
T & Vector<T>::at(const std::size_t & index) {
    if (index >= size_) {
        throw "List index out of range";
    }
    return data_[index];
}

template<class T>
const T & Vector<T>::at(const std::size_t & index) const {
    if (index >= size_) {
        throw "List index out of range";
    }
    return data_[index];
}

template<class T>
std::size_t Vector<T>::size() const {
    return size_;
}

template<class T>
std::size_t Vector<T>::capacity() const {
    return capacity_;
}

template<class T>
T & Vector<T>::front() {
    return data_[0];
}

template<class T>
const T & Vector<T>::front() const {
    return data_[0];
}

template<class T>
T & Vector<T>::back() {
    return data_[size_ - 1];
}

template<class T>
const T & Vector<T>::back() const {
    return data_[size_ - 1];
}

template<class T>
T * Vector<T>::data() {
    return data_;
}

template<class T>
const T * const Vector<T>::data() const {
    return const_cast<const T* const>(data_);
}

template<class T>
bool Vector<T>::empty() const {
    return size_;
}

template<class T>
void Vector<T>::resize(const std::size_t & sz) {
    size_ = sz;
    if (size_ + 1 >= capacity_) {
        capacity_ = size_;
        realloc(capacity_);
    }
}

template<class T>
void Vector<T>::reserve(const std::size_t & cap) {
    capacity_ = cap;
    realloc(capacity_);
}


template<class T>
void Vector<T>::realloc(const std::size_t& cap) {
    auto copy_ = new T[cap];
    for (std::size_t _ = 0; _ < this->size_; ++_) {
        copy_[_] = data_[_];
    }
    delete[] data_;
    data_ = copy_;
}
#endif
