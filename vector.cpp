#include "vector.h"
#include <exception>

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

template<class T>
void Vector<T>::push_back(const T & val) {
    ++size_;
    if (size_ >= capacity_) {
        capacity_ *= 2;
        realloc(capacity_);
    }
    array_[size_ - 1] = val;
}

template<class T>
void Vector<T>::pop_back() {
    --size_;
}

template<class T>
void Vector<T>::emplace_back(T && val) {
    ++size_;
    if (size_ >= capacity_) {
        capacity_ *= 2;
        realloc(capacity_);
    }

    std::swap(array_[size_ - 1], val);
}

template<class T>
T & Vector<T>::operator[](const std::size_t & index) {
    return array_[index];
}

template<class T>
const T & Vector<T>::operator[](const std::size_t & index) const {
    return array_[index];
}

template<class T>
T & Vector<T>::at(const std::size_t & index) {
    if (index >= size_) {
        throw "List index out of range";
    }
    return array_[index];
}

template<class T>
const T & Vector<T>::at(const std::size_t & index) const {
    if (index >= size_) {
        throw "List index out of range";
    }
    return array_[index];
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
    return array_[0];
}

template<class T>
const T & Vector<T>::front() const {
    return array_[0];
}

template<class T>
T & Vector<T>::back() {
    return array_[size_ - 1];
}

template<class T>
const T & Vector<T>::back() const {
    return array_[size_ - 1];
}

template<class T>
T * Vector<T>::data() {
    return array_;
}

template<class T>
const T * const Vector<T>::data() const {
    return const_cast<const T* const>(array_);
}

template<class T>
bool Vector<T>::empty() const {
    return size_;
}

template<class T>
void Vector<T>::resize(const std::size_t & sz) {
    size_ = sz;
    if (size_ >= capacity_) {
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
        copy_[_] = array_[_];
    }
    delete[] array_;
    array_ = copy_;
}
