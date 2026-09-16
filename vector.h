#ifndef vector_h
#define vector_h
#include <utility>

template<class T>
class Vector {
  private:
    T* array_;
    std::size_t size_;
    std::size_t capacity_;
  public:
    explicit Vector(const std::size_t&, const T&);
    explicit Vector(const std::size_t&);
    Vector(const std::initializer_list<T>&);
    Vector(const Vector&);
    Vector(Vector&&) noexcept;

    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&) noexcept;

    Vector& operator=(const std::initializer_list<T>&);

    ~Vector();
};

#endif
