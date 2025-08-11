#pragma once


#include "list.h"

#include <cassert>
#include <forward_list>
#include <list>
#include <type_traits>
#include <algorithm>
#include <sstream>


void CheckLists(const List& actual, const std::forward_list<int32_t>& expected) {
    List::ListIterator actual_it = actual.begin();
    std::forward_list<int32_t>::const_iterator expected_it = expected.begin();
    for (; actual_it != actual.end() && expected_it != expected.cend();
         ++actual_it, ++expected_it) {
        assert(*actual_it == *expected_it);
    }
    assert(actual_it == actual.end() && expected_it == expected.cend());
}

void default_constructible_tests() {
    static_assert(std::is_default_constructible_v<List>, "No default constructor!");
    // default constructor test
    {
        List a;
        assert(a.Size() == 0u);
        CheckLists(a, std::forward_list<int32_t>());
    }
}

void simple_push_pop_tests() {
    // simple tests
    {
        List a;
        a.PushFront(1);
        assert(a.Size() == 1u);
        assert(a.Front() == 1);
        CheckLists(a, std::forward_list<int32_t>{1});

        a.PushFront(2);
        assert(a.Size() == 2u);
        assert(a.Front() == 2);
        CheckLists(a, std::forward_list<int32_t>{2, 1});

        a.PopFront();
        assert(a.Size() == 1u);
        assert(a.Front() == 1);
        CheckLists(a, std::forward_list<int32_t>{1});
    }

    {
        List a;
        a.PushFront(1);
        a.PushFront(5);
        a.PushFront(1);
        a.PushFront(3);
        a.PushFront(2);
        a.PushFront(1);

        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 1, 5, 1});
        a.PopFront();
        a.PopFront();
        a.PopFront();
        CheckLists(a, std::forward_list<int32_t>{1, 5, 1});
    }
}

void copying_tests() {
    static_assert(std::is_copy_constructible_v<List>, "No copy constructor!");
    // copying tests
    {
        List a;
        a.PushFront(7);
        a.PushFront(6);
        a.PushFront(5);
        a.PushFront(4);
        a.PushFront(3);
        a.PushFront(2);
        a.PushFront(1);
        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6, 7});

        List b = a;
        assert(b.Size() == 7u);
        assert(b.Front() == a.Front());
        assert(b.FindByValue(5));
        assert(!b.FindByValue(10));
        CheckLists(b, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6, 7});

        List c;
        c = b;
        assert(c.Size() == 7u);
        assert(c.Front() == a.Front());
        assert(c.FindByValue(5));
        assert(!c.FindByValue(10));
        CheckLists(c, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6, 7});
    }
}

void clear_tests() {

    // clear empty list
    {
        List a;
        a.Clear();
        assert(a.Size() == 0u);
        CheckLists(a, std::forward_list<int32_t>());
    }

    // clear tests
    {
        List a;
        a.PushFront(6);
        a.PushFront(5);
        a.PushFront(4);
        a.PushFront(3);
        a.PushFront(2);
        a.PushFront(1);

        assert(a.Size() == 6u);
        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6});

        a.Clear();
        assert(a.Size() == 0u);
        CheckLists(a, std::forward_list<int32_t>());
    }
}

void iterator_tests() {
    // simple iterator tests
    {
        List a;
        a.PushFront(6);
        a.PushFront(5);
        a.PushFront(4);
        a.PushFront(3);
        a.PushFront(2);
        a.PushFront(1);

        List::ListIterator it = a.begin();
        assert(*it == 1);
        assert(*(it.operator->()) == 1);
        ++it;
        assert(*it == 2);
        assert(*(it.operator->()) == 2);

        List::ListIterator it2 = a.begin();
        it2++;
        assert(*it2 == 2);
        assert(*(it.operator->()) == 2);
        assert(it == it2);

        List::ListIterator it3 = a.begin();
        assert(it != it3 && it2 != it3);
    }

    // modifications with iterators
    {
        List a;
        a.PushFront(5);
        a.PushFront(3);
        a.PushFront(1);
        *(a.begin().operator->()) = 3;
        *((++a.begin()).operator->()) = 4;

        CheckLists(a, std::forward_list<int32_t>{3, 4, 5});
        List::ListIterator it = a.begin();
        ++it;
        assert(*it == 4);
    }

    // iterator loop tests
    {
        List a;
        a.PushFront(6);
        a.PushFront(5);
        a.PushFront(4);
        a.PushFront(3);
        a.PushFront(2);
        a.PushFront(1);

        List::ListIterator it = a.begin();
        ++it;

        // std::copy test
        std::stringstream sstream;
        std::copy(it, a.end(), std::ostream_iterator<int32_t>(sstream));
        assert(sstream.str() == "23456");

        sstream.str("");

        // for-loop tests
        for (auto iter = a.begin(); iter != a.end(); ++iter) {
            sstream << *iter;
        }
        assert(sstream.str() == "123456");

        sstream.str("");

        for (int32_t item : a) {
            sstream << item;
        }
        assert(sstream.str() == "123456");

        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6});
    }
}

void remove_tests() {
    // remove single elements
    {
        List a;
        a.PushFront(6);
        a.PushFront(5);
        a.PushFront(4);
        a.PushFront(3);
        a.PushFront(2);
        a.PushFront(1);
        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6});

        a.Remove(4);
        assert(a.Size() == 5u);
        assert(a.Front() == 1);
        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 5, 6});

        a.Remove(1);
        assert(a.Size() == 4u);
        assert(a.Front() == 2);
        CheckLists(a, std::forward_list<int32_t>{2, 3, 5, 6});

        a.Remove(6);
        assert(a.Size() == 3u);
        assert(a.Front() == 2);
        CheckLists(a, std::forward_list<int32_t>{2, 3, 5});
    }

    // remove repeated elements
    {
        List a;
        a.PushFront(1);
        a.PushFront(8);
        a.PushFront(1);
        a.PushFront(5);
        a.PushFront(2);
        a.PushFront(1);
        a.PushFront(1);
        a.PushFront(1);
        assert(a.Size() == 8u);
        CheckLists(a, std::forward_list<int32_t>{1, 1, 1, 2, 5, 1, 8, 1});

        a.Remove(1);
        assert(a.Size() == 3u);
        CheckLists(a, std::forward_list<int32_t>{2, 5, 8});
    }
}

void output_tests() {
    // empty list
    {
        List a;
        assert(a.Size() == 0u);
        CheckLists(a, std::forward_list<int32_t>{});

        std::stringstream sstream;
        a.Print(sstream);
        assert(sstream.str().empty());
    }

    // non-empty lists
    {
        List a;
        a.PushFront(6);
        assert(a.Size() == 1u);
        CheckLists(a, std::forward_list<int32_t>{6});

        std::stringstream sstream;
        a.Print(sstream);
        assert(sstream.str() == "6");
    }

    {
        List a;
        a.PushFront(6);
        a.PushFront(5);
        a.PushFront(4);
        a.PushFront(3);
        a.PushFront(2);
        a.PushFront(1);
        assert(a.Size() == 6u);
        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6});

        std::stringstream sstream;
        a.Print(sstream);
        assert(sstream.str() == "1 2 3 4 5 6");
    }
}

