#include "vector.h"

template<class T>
Vector<T>::Vector(const std::size_t& sz, const T& val) :
data_(new T[sz]), size_(sz), capacity_(sz) {
    for (std::size_t _ = 0; _ < size_; ++_) {
        data_[_] = val;
    }
}

template<class T>
Vector<T>::Vector(const std::size_t & sz) :
data_(new T[sz]), size_(sz), capacity_(sz) {}

template<class T>
Vector<T>::Vector(const std::initializer_list<T> & list) :
data_(new T[list.size()]), size_(list.size()), capacity_(list.size()) {
    for (std::size_t _ = 0; _ < this->size_; ++_) {
        data_[_] = list[_];
    }
}

template<class T>
Vector<T>::Vector(const Vector & other) {
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;
    data_ = new T[this->size_];
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
    delete[] data_;
    this->Vector(other);
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
    delete[] this->data_;
    this->Vector(list);
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
    if (size_ >= capacity_) {
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
    if (size_ >= capacity_) {
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
        copy_[_] = data_[_];
    }
    delete[] data_;
    data_ = copy_;
}
