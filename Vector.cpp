#include "Vector.h"
#include <exception>
#include <string>
#include <utility>

#ifndef vector_cpp
#define vector_cpp

class OutOfRange : std::exception {
  public:
    explicit OutOfRange(std::string s) : s_(std::move(s)) {}
    [[nodiscard]] const char* what() const noexcept override { return s_.c_str(); }
  private:
    std::string s_;
};

class NoFront : std::exception {
public:
    explicit NoFront(std::string s) : s_(std::move(s)) {}
    [[nodiscard]] const char* what() const noexcept override { return s_.c_str(); }
private:
    std::string s_;
};

class NoBack : std::exception {
public:
    explicit NoBack(std::string s) : s_(std::move(s)) {}
    [[nodiscard]] const char* what() const noexcept override { return s_.c_str(); }
private:
    std::string s_;
};


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
    std::size_t ind = 0;
    for (auto& _: list) {
        data_[ind] = _;
        ++ind;
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
data_(nullptr) {
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
    this->capacity_ = list.size();
    delete[] this->data_;
    this->data_ = new T[this->capacity_];
    std::size_t ind = 0;
    for (auto& _: list) {
        data_[ind] = _;
        ++ind;
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
    if (size_ + 1 >= capacity_) {
        capacity_ *= 2;
        realloc(capacity_);
    }
    data_[size_] = val;

    ++size_;
}

template<class T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

// template<class T>
// void Vector<T>::emplace_back(T && val) {
//     if (size_ + 1 >= capacity_) {
//         capacity_ *= 2;
//         realloc(capacity_);
//     }
//
//     std::swap(data_[size_], val);
//     ++size_;
// }

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
        throw OutOfRange("List index out of range");
    }
    return data_[index];
}

template<class T>
const T & Vector<T>::at(const std::size_t & index) const {
    if (index >= size_) {
        throw OutOfRange("List index out of range");
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
    if (size_ == 0) {
        throw NoFront("Vector doesn't have any elements");
    }
    return data_[0];
}

template<class T>
const T & Vector<T>::front() const {
    if (size_ == 0) {
        throw NoFront("Vector doesn't have any elements");
    }
    return data_[0];
}

template<class T>
T & Vector<T>::back() {
    if (size_ == 0) {
        throw NoBack("Vector doesn't have any elements");
    }
    return data_[size_ - 1];
}

template<class T>
const T & Vector<T>::back() const {
    if (size_ == 0) {
        throw NoBack("Vector doesn't have any elements");
    }
    return data_[size_ - 1];
}

template<class T>
T * Vector<T>::data() {
    return data_;
}

template<class T>
const T * Vector<T>::data() const {
    return const_cast<const T* const>(data_);
}

template<class T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

template<class T>
void Vector<T>::clear() {
    delete[] data_;
    capacity_ = 1;
    size_ = 0;
    data_ = nullptr;
}

template<class T>
void Vector<T>::resize(const std::size_t & sz) {
    if (sz >= capacity_) {
        capacity_ = sz;
        realloc(capacity_);
    }

    size_ = sz;
}

template<class T>
void Vector<T>::reserve(const std::size_t & cap) {
    if (cap > capacity_) {
        capacity_ = cap;
        realloc(capacity_);
    }
}


template<class T>
void Vector<T>::realloc(const std::size_t& cap) {
    if (cap == 0) {
        delete[] data_;
        return;
    }
    auto copy_ = new T[cap]{};
    if (data_ != nullptr) {
        for (std::size_t _ = 0; _ < this->size_; ++_) {
            copy_[_] = data_[_];
        }
    }
    delete[] data_;
    data_ = copy_;
}
#endif
