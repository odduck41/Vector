#pragma once
#include <iostream>
#include "vector.hpp"

namespace bns {
    template <class T>
    class Stack {
    public:
        Stack() = default;

        Stack(const Stack& other) {
            if (other.head_ == nullptr) return;
            this->head_ = new T(other.head_->val);
            auto this_ptr = head_;
            auto other_ptr = other.head_;
            while (other_ptr->next != nullptr) {
                this_ptr->next = new T(other_ptr->val);
                this_ptr = this_ptr->next;
                other_ptr = other_ptr->next;
            }
        }
        Stack& operator=(const Stack& other) {
            if (this == &other) return *this;
            if (other.head_ == nullptr) return *this;
            this->~Stack();

            this->head_ = new Node(other.head_->val);
            auto this_ptr = head_;
            auto other_ptr = other.head_;
            while (other_ptr->next != nullptr) {
                this_ptr->next = new Node(other_ptr->val);
                this_ptr = this_ptr->next;
                other_ptr = other_ptr->next;
            }
            return *this;
        }

        friend std::ofstream& operator<< (std::ofstream&, Stack<T>);

        void push(const T& element) {
            auto ptr = new Node(element, head_);
            head_ = ptr;
        }
        T& top() {
            return head_->val;
        }
        const T& top() const {
            return head_->val;
        }
        void pop() {
            auto ptr = head_->next;
            delete head_;
            head_ = ptr;
        }

        ~Stack() {
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