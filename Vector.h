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

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::size_t capacity() const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T* data();
    const T* const data() const;

    [[nodiscard]] bool empty() const;

    void resize(const std::size_t&);
    void reserve(const std::size_t&);


    struct iterator {
      public:
        explicit iterator(T* v_) : value_(v_) {}
        T& operator*() {
          return *value_;
        }
        iterator operator+(const std::size_t& jmp) {
          iterator x(value_ + jmp);
          return x;
        }

        iterator& operator++() {
          ++value_;
          return *this;
        }

        iterator operator++(int) {
          iterator x(value_);
          ++value_;
          return x;
        }

        iterator operator-(const std::size_t& jmp) {
            iterator x(value_ - jmp);
            return x;
        }

        iterator& operator--() {
            --value_;
            return *this;
        }

        iterator operator--(int) {
            iterator x(value_);
            --value_;
            return x;
        }

        bool operator==(const iterator &) const = default;
     private:
      T* value_{};
    };
    iterator begin() {
      return iterator(data_);
    }
    iterator end() {
      return iterator(data_ + size_);
    }
/* TODO:
 * push_back +
 * pop_back +
 * emplace_back +
 * operator[] +
 * at +
 * size() +
 * capacity() +
 * front +
 * data +
 * iterators ?
 * empty +
 * clear +
 * resize +
 * reserve +
*/
  private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void realloc(const std::size_t&);
};

#include "Vector.cpp"
#endif
