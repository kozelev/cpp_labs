#pragma once

#include <iterator>
#include <iostream>

class List {

private:
    struct Node {
        int32_t value_;
        Node* next_;

        explicit Node(int value) : value_(value), next_(nullptr) {
        }
    };

public:
    struct ListIterator {

        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int32_t;
        using pointer           = value_type*;
        using reference         = value_type&;

        explicit ListIterator(Node* position) : position_(position) {
        }

        ListIterator& operator++() { // prefix
            if (position_ != nullptr) {
                position_ = position_->next_;
            }
            return *this;
        }

        ListIterator operator++(int) { // postfix
            ListIterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(const ListIterator& other) const {
            return position_ == other.position_;
        }

        bool operator!=(const ListIterator& other) const {
            return !(*this == other);
        }

        reference operator*() const {
            return position_->value_;
        }

        pointer operator->() {
            return &position_->value_;
        }

        Node* position_;
    };

    // methods for "ranged-based for loop"
    // 1) non-const version
    ListIterator begin() {
        // your code goes here
    }
    ListIterator end() {
        // your code goes here
    }
    
    // 2) const version
    // TODO: think about return type(is it exactly ListIterator?)
    ListIterator begin() const {
        // your code goes here
    }
    ListIterator end() const {
        // your code goes here
    }

    // default constructor
    List();

    // copy constructor
    List(const List& rhs);

    // operator= overloading
    List& operator=(const List& rhs);

    // destructor
    ~List();

    // insert new element on the top of the list
    void PushFront(int32_t value);

    // delete first element of the list
    void PopFront();

    // remove every occurence of an element in the list whose value equal to param "value",
    // the remaining elements must remain in the same order
    void Remove(int32_t value);

    // erases all the elements
    void Clear();

    // find list's element by the value
    // returns true, if element exists
    // otherwise, returns false
    bool FindByValue(int32_t value);

    // print list's elements to stream separated by space
    void Print(std::ostream& out);

    // get first element of the list
    int32_t Front() const;

    // get size of the list
    size_t Size() const;

private:
    // your code goes here
};
