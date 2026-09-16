#ifndef vector_h
#define vector_h
#include <utility>

template<class T>
class Vector {
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

    void push_back(const T&);
    void pop_back();

    void emplace_back(T&&);

    T& operator[](const std::size_t&);
    const T& operator[](const std::size_t&) const;

    T& at(const std::size_t&);
    const T& at(const std::size_t&) const;

    std::size_t size() const;
    std::size_t capacity() const;

    T& front();
    const T& front() const;

    T* data();
    const T* const data() const;

    bool empty();

    void resize(const std::size_t&);
    void reserve(const std::size_t&);


/* TODO:
 * push_back
 * pop_back
 * emplace_back
 * operator[]
 * at
 * size()
 * capacity()
 * front
 * data
 * iterators
 * empty
 * clear
 * resize
 * reserve
*/
  private:
    T* array_;
    std::size_t size_;
    std::size_t capacity_;

    void realloc(const std::size_t&);
};

#endif
