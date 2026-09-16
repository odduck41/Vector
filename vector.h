#ifndef vector_h
#define vector_h
#include <utility>

template<class T>
class Vector {
  private:
    T* array_;
    std::size_t size_;
    std::size_t capacity;
  public:
    explicit Vector(const std::size_t&);
    Vector(const Vector&);
    Vector(Vector&&);

    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);

    Vector& operator=(std::initializer_list<T>);

    ~Vector();
};

#endif
