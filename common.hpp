#pragma once
#include <exception>
#include <utility>

namespace bns {
    template<class T>
    concept Printable = requires(T t)
    {
        {std::cout << t} -> std::same_as<std::ostream&>;
    };

    template<typename T>
    std::string_view type_name() {
        constexpr std::string_view res = __PRETTY_FUNCTION__;
        constexpr auto begin = res.rfind("T = ");
        constexpr auto end = res.rfind(']');
        return res.substr(begin + 4, end - (begin + 4));
    }

    class Error : std::exception {
    public:
        explicit Error(std::string msg) : msg_(std::move(msg)) {};
        [[nodiscard]] const char* what() const noexcept override {
            return msg_.c_str();
        };
    private:
        std::string msg_;
    };

    class RangeLimit : public Error {
    public:
        explicit RangeLimit(const size_t& a, /* > */ const size_t& b) :
        Error(std::format("Array size {} is less than your index {}", a, b)) {};
    };

    class Empty : public Error {
    public:
        explicit Empty() : Error("Container is empty") {}
    };
}
