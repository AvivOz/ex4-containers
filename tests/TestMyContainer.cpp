// author: avivoz4@gmail.com

/**
 * @file TestMyContainer.cpp
 * @brief Test suite for MyContainer class
 * @author Aviv Oz
 * @date 2025-06-06 15:42:33
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/MyContainer.hpp"
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

using namespace containers;

TEST_CASE("Basic Container Operations") {
    MyContainer<int> container;

    SUBCASE("Initial state") {
        CHECK(container.size() == 0);
    }

    SUBCASE("Adding elements") {
        container.add(1);
        CHECK(container.size() == 1);
        CHECK(container[0] == 1);

        container.add(2);
        CHECK(container.size() == 2);
        CHECK(container[1] == 2);
    }

    SUBCASE("Removing elements") {
        container.add(1);
        container.add(2);
        container.add(3);

        container.remove(2);
        CHECK(container.size() == 2);
        CHECK(container[0] == 1);
        CHECK(container[1] == 3);

        CHECK_THROWS_AS(container.remove(4), std::runtime_error);
    }

    SUBCASE("Array access operator") {
        container.add(1);
        container.add(2);

        CHECK(container[0] == 1);
        CHECK(container[1] == 2);
        CHECK_THROWS_AS(container[2], std::out_of_range);
    }

    SUBCASE("Const array access operator") {
        container.add(1);
        const MyContainer<int>& const_container = container;
        CHECK(const_container[0] == 1);
        CHECK_THROWS_AS(const_container[1], std::out_of_range);
    }
}

TEST_CASE("Output Stream Operator") {
    MyContainer<int> container;
    
    SUBCASE("Empty container") {
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[]");
    }

    SUBCASE("Container with elements") {
        container.add(1);
        container.add(2);
        container.add(3);
        std::stringstream ss;
        ss << container;
        CHECK(ss.str() == "[1,2,3]");
    }
}

TEST_CASE("Iterator Functionality") {
    MyContainer<int> container;
    for (int i = 1; i <= 4; i++) {
        container.add(i);
    }

    SUBCASE("Copy Constructor and Assignment") {
        SUBCASE("Order Iterator") {
            auto it1 = container.order();
            auto it2(it1);  // copy constructor
            auto it3 = it1; // assignment operator
            
            CHECK(*it1 == *it2);
            CHECK(*it1 == *it3);
            ++it1;
            CHECK(*it1 != *it2);
        }

        SUBCASE("ReverseOrder Iterator") {
            auto it1 = container.reverse_order();
            auto it2(it1);
            auto it3 = it1;
            
            CHECK(*it1 == *it2);
            CHECK(*it1 == *it3);
            ++it1;
            CHECK(*it1 != *it2);
        }

        SUBCASE("AscendingOrder Iterator") {
            auto it1 = container.ascending_order();
            auto it2(it1);
            auto it3 = it1;
            
            CHECK(*it1 == *it2);
            CHECK(*it1 == *it3);
            ++it1;
            CHECK(*it1 != *it2);
        }

        SUBCASE("DescendingOrder Iterator") {
            auto it1 = container.descending_order();
            auto it2(it1);
            auto it3 = it1;
            
            CHECK(*it1 == *it2);
            CHECK(*it1 == *it3);
            ++it1;
            CHECK(*it1 != *it2);
        }

        SUBCASE("SideCrossOrder Iterator") {
            auto it1 = container.side_cross_order();
            auto it2(it1);
            auto it3 = it1;
            
            CHECK(*it1 == *it2);
            CHECK(*it1 == *it3);
            ++it1;
            CHECK(*it1 != *it2);
        }

        SUBCASE("MiddleOutOrder Iterator") {
            auto it1 = container.middle_out_order();
            auto it2(it1);
            auto it3 = it1;
            
            CHECK(*it1 == *it2);
            CHECK(*it1 == *it3);
            ++it1;
            CHECK(*it1 != *it2);
        }
    }
}

TEST_CASE("Iterator Comparison and End State") {
    MyContainer<int> container;
    container.add(1);

    SUBCASE("Order Iterator") {
        auto it = container.order();
        auto end = it.end();
        CHECK_THROWS_AS(*end, std::out_of_range);
        ++it;
        CHECK(it == end);
        ++it;  // נוסף increment נוסף
        CHECK(it == end);  // צריך להישאר במצב end
    }

    SUBCASE("ReverseOrder Iterator") {
        auto it = container.reverse_order();
        auto end = it.end();
        CHECK_THROWS_AS(*end, std::out_of_range);
        ++it;
        CHECK(it == end);
        ++it;
        CHECK(it == end);
    }

    SUBCASE("AscendingOrder Iterator") {
        auto it = container.ascending_order();
        auto end = it.end();
        CHECK_THROWS_AS(*end, std::out_of_range);
        ++it;
        CHECK(it == end);
        ++it;
        CHECK(it == end);
    }

    SUBCASE("DescendingOrder Iterator") {
        auto it = container.descending_order();
        auto end = it.end();
        CHECK_THROWS_AS(*end, std::out_of_range);
        ++it;
        CHECK(it == end);
        ++it;
        CHECK(it == end);
    }

    SUBCASE("SideCrossOrder Iterator") {
        auto it = container.side_cross_order();
        auto end = it.end();
        CHECK_THROWS_AS(*end, std::out_of_range);
        ++it;
        CHECK(it == end);
        ++it;
        CHECK(it == end);
    }

    SUBCASE("MiddleOutOrder Iterator") {
        auto it = container.middle_out_order();
        auto end = it.end();
        CHECK_THROWS_AS(*end, std::out_of_range);
        ++it;
        CHECK(it == end);
        ++it;
        CHECK(it == end);
    }
}

TEST_CASE("Iterator Post-Increment") {
    MyContainer<int> container;
    container.add(1);
    container.add(2);

    SUBCASE("Order Iterator") {
        auto it = container.order();
        auto old = it++;
        CHECK(*old == 1);
        CHECK(*it == 2);
    }

    SUBCASE("ReverseOrder Iterator") {
        auto it = container.reverse_order();
        auto old = it++;
        CHECK(*old == 2);
        CHECK(*it == 1);
    }

    SUBCASE("AscendingOrder Iterator") {
        auto it = container.ascending_order();
        auto old = it++;
        CHECK(*old == 1);
        CHECK(*it == 2);
    }

    SUBCASE("DescendingOrder Iterator") {
        auto it = container.descending_order();
        auto old = it++;
        CHECK(*old == 2);
        CHECK(*it == 1);
    }

    SUBCASE("SideCrossOrder Iterator") {
        auto it = container.side_cross_order();
        auto old = it++;
        CHECK(*old == 1);
        CHECK(*it == 2);
    }

    SUBCASE("MiddleOutOrder Iterator") {
        auto it = container.middle_out_order();
        auto old = it++;
        CHECK(*old == 1);
        CHECK(*it == 2);
    }
}

TEST_CASE("Iterator Order Verification") {
    MyContainer<int> container;
    std::vector<int> values = {3, 1, 4, 2};
    for (int val : values) {
        container.add(val);
    }

    SUBCASE("Regular Order") {
        std::vector<int> expected = {3, 1, 4, 2};
        auto it = container.order();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }

    SUBCASE("Reverse Order") {
        std::vector<int> expected = {2, 4, 1, 3};
        auto it = container.reverse_order();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }

    SUBCASE("Ascending Order") {
        std::vector<int> expected = {1, 2, 3, 4};
        auto it = container.ascending_order();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }

    SUBCASE("Descending Order") {
        std::vector<int> expected = {4, 3, 2, 1};
        auto it = container.descending_order();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }

    SUBCASE("Side Cross Order") {
        std::vector<int> expected = {1, 4, 2, 3};
        auto it = container.side_cross_order();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }
}

TEST_CASE("Middle Out Special Cases") {
    MyContainer<int> container;
    
    SUBCASE("Even number of elements") {
        std::vector<int> values = {1, 2, 3, 4};
        for (int val : values) {
            container.add(val);
        }
        std::vector<int> expected = {2, 3, 1, 4};
        
        auto it = container.middle_out_order();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }

    SUBCASE("Odd number of elements") {
        std::vector<int> values = {1, 2, 3, 4, 5};
        for (int val : values) {
            container.add(val);
        }
        std::vector<int> expected = {3, 2, 4, 1, 5};
        
        auto it = container.middle_out_order();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }
}

TEST_CASE("Edge Cases") {
    SUBCASE("Empty Container Operations") {
        MyContainer<int> container;
        CHECK_THROWS_AS(container[0], std::out_of_range);
        CHECK_THROWS_AS(container.remove(1), std::runtime_error);
        
        auto order_it = container.order();
        CHECK(order_it.begin() == order_it.end());
        
        auto reverse_it = container.reverse_order();
        CHECK(reverse_it.begin() == reverse_it.end());
        
        auto asc_it = container.ascending_order();
        CHECK(asc_it.begin() == asc_it.end());
        
        auto desc_it = container.descending_order();
        CHECK(desc_it.begin() == desc_it.end());
        
        auto cross_it = container.side_cross_order();
        CHECK(cross_it.begin() == cross_it.end());
        
        auto middle_it = container.middle_out_order();
        CHECK(middle_it.begin() == middle_it.end());
    }

    SUBCASE("Single Element Container") {
        MyContainer<int> container;
        container.add(1);
        
        auto order_it = container.order();
        CHECK(*order_it.begin() == 1);
        
        auto reverse_it = container.reverse_order();
        CHECK(*reverse_it.begin() == 1);
        
        auto asc_it = container.ascending_order();
        CHECK(*asc_it.begin() == 1);
        
        auto desc_it = container.descending_order();
        CHECK(*desc_it.begin() == 1);
        
        auto cross_it = container.side_cross_order();
        CHECK(*cross_it.begin() == 1);
        
        auto middle_it = container.middle_out_order();
        CHECK(*middle_it.begin() == 1);
    }
}

TEST_CASE("Iterator Safety") {
    MyContainer<int> container;
    container.add(1);
    container.add(2);

    SUBCASE("Multiple increments beyond end") {
        auto it = container.order();
        ++it;
        ++it;
        ++it; // Should not throw, just stay at end
        CHECK(it == it.end());
        ++it; // Additional increment
        CHECK(it == it.end()); // Should still be at end
    }

}

TEST_CASE("Container with Different Types") {
    SUBCASE("String container") {
        MyContainer<std::string> container;
        container.add("hello");
        container.add("world");
        
        auto it = container.ascending_order();
        CHECK(*it == "hello");
        ++it;
        CHECK(*it == "world");
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Double container") {
        MyContainer<double> container;
        container.add(1.5);
        container.add(1.1);
        container.add(1.9);
        
        auto it = container.ascending_order();
        std::vector<double> expected = {1.1, 1.5, 1.9};
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
    }
}

TEST_CASE("Performance Tests") {
    MyContainer<int> container;
    const int SIZE = 10000;

    SUBCASE("Large number of elements") {
        for (int i = 0; i < SIZE; ++i) {
            container.add(i);
        }
        CHECK(container.size() == SIZE);

        auto asc_it = container.ascending_order();
        int prev = -1;
        for (const auto& val : asc_it) {
            CHECK(val > prev);
            prev = val;
        }
    }
}

TEST_CASE("Iterator Multiple Operations") {
    MyContainer<int> container;
    for(int i = 1; i <= 4; ++i) {
        container.add(i);
    }

    SUBCASE("Multiple Operations on Same Iterator") {
        auto it = container.order();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        auto it2 = it;
        ++it;
        CHECK(*it == 3);
        CHECK(*it2 == 2);
    }

    SUBCASE("Multiple Iterators on Same Container") {
        auto it1 = container.order();
        auto it2 = container.order();
        CHECK(*it1 == *it2);
        ++it1;
        CHECK(*it1 == 2);
        CHECK(*it2 == 1);
    }
}