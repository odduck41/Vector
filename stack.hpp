#pragma once
#include <iostream>

#include "common.hpp"

namespace bns {
    template <class T>
    class stack {
    public:
        stack() = default;

        stack(const stack& other) {
            if (other.head_ == nullptr) return;
            this->head_ = new Node(other.head_->val);
            auto this_ptr = head_;
            auto other_ptr = other.head_->next;
            while (other_ptr != nullptr) {
                this_ptr->next = new Node(other_ptr->val);
                this_ptr = this_ptr->next;
                other_ptr = other_ptr->next;
            }
        }
        stack& operator=(const stack& other) {
            if (this == &other) return *this;
            if (other.head_ == nullptr) return *this;
            this->~Stack();

            this->head_ = new Node(other.head_->val);
            auto this_ptr = head_;
            auto other_ptr = other.head_->next;
            while (other_ptr != nullptr) {
                this_ptr->next = new Node(other_ptr->val);
                this_ptr = this_ptr->next;
                other_ptr = other_ptr->next;
            }
            return *this;
        }

        friend std::ostream& operator<< (std::ostream& os, stack<T> s)
        requires Printable<T> {
            os << std::format("stack<{}>", type_name<T>()) << "{";
            if (s.head_ == nullptr) {
                os << "}";
                return os;
            }
            os << "[" << s.head_->val << "]";
            auto ptr = s.head_->next;
            while (ptr != nullptr) {
                os << ", " << ptr->val;
                ptr = ptr->next;
            }
            os << "}";
            return os;
        }

        void push(const T& element) {
            auto ptr = new Node(element, head_);
            head_ = ptr;
        }
        T& top() {
            if (head_ == nullptr) throw Empty(); // DONE: add exception(!)
            return head_->val;
        }
        const T& top() const {
            if (head_ == nullptr) throw Empty(); // DONE: add exception(!)
            return head_->val;
        }
        void pop() {
            if (head_ == nullptr) throw Empty(); // DONE: add exception(!)
            auto ptr = head_->next;
            delete head_;
            head_ = ptr;
        }

        ~stack() {
            if (head_ == nullptr) return;
            auto ptr = head_;
            auto next = ptr->next;
            delete ptr;
            while (next != nullptr) {
                ptr = next;
                next = ptr->next;
                delete ptr;
            }
        }
    private:
        struct Node {
            T val{};
            Node* next{};
        };
        Node* head_{};
    };
}