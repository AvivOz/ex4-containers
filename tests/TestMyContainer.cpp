// author: avivoz4@gmail.com

/**
 * @file TestMyContainer.cpp
 * @brief Test suite for MyContainer class
 * @author Aviv Oz
 * @date 2025-06-05 13:46:18
 */

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

TEST_CASE("Regular Order Iterator") {
    MyContainer<int> container;
    
    SUBCASE("Empty container") {
        auto it = container.getOrder();
        CHECK(it.begin() != it.end());
    }

    SUBCASE("Container with elements") {
        std::vector<int> values = {3, 1, 4, 2};
        for (int val : values) {
            container.add(val);
        }

        auto it = container.getOrder();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == values[i++]);
        }
        CHECK(i == values.size());
    }
}

TEST_CASE("Reverse Order Iterator") {
    MyContainer<int> container;
    
    SUBCASE("Empty container") {
        auto it = container.getReverseOrder();
        CHECK(it.begin() != it.end());
    }

    SUBCASE("Container with elements") {
        std::vector<int> values = {3, 1, 4, 2};
        std::vector<int> expected = {2, 4, 1, 3};
        for (int val : values) {
            container.add(val);
        }

        auto it = container.getReverseOrder();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }
}

TEST_CASE("Ascending Order Iterator") {
    MyContainer<int> container;
    
    SUBCASE("Empty container") {
        auto it = container.getAscendingOrder();
        CHECK(it.begin() != it.end());
    }

    SUBCASE("Container with elements") {
        std::vector<int> values = {3, 1, 4, 2};
        std::vector<int> expected = {1, 2, 3, 4};
        for (int val : values) {
            container.add(val);
        }

        auto it = container.getAscendingOrder();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }
}

TEST_CASE("Descending Order Iterator") {
    MyContainer<int> container;
    
    SUBCASE("Empty container") {
        auto it = container.getDescendingOrder();
        CHECK(it.begin() != it.end());
    }

    SUBCASE("Container with elements") {
        std::vector<int> values = {3, 1, 4, 2};
        std::vector<int> expected = {4, 3, 2, 1};
        for (int val : values) {
            container.add(val);
        }

        auto it = container.getDescendingOrder();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }
}

TEST_CASE("Side Cross Order Iterator") {
    MyContainer<int> container;
    
    SUBCASE("Empty container") {
        auto it = container.getSideCrossOrder();
        CHECK(it.begin() != it.end());
    }

    SUBCASE("Container with elements") {
        std::vector<int> values = {3, 1, 4, 2};
        std::vector<int> expected = {1, 4, 2, 3};  // smallest, largest, second smallest, second largest
        for (int val : values) {
            container.add(val);
        }

        auto it = container.getSideCrossOrder();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }

    SUBCASE("Odd number of elements") {
        std::vector<int> values = {3, 1, 4, 2, 5};
        std::vector<int> expected = {1, 5, 2, 4, 3};
        for (int val : values) {
            container.add(val);
        }

        auto it = container.getSideCrossOrder();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }
}

TEST_CASE("Middle Out Order Iterator") {
    MyContainer<int> container;
    
    SUBCASE("Empty container") {
        auto it = container.getMiddleOutOrder();
        CHECK(it.begin() != it.end());
    }

    SUBCASE("Even number of elements") {
        std::vector<int> values = {1, 2, 3, 4};
        std::vector<int> expected = {2, 1, 3, 4};  // middle, left, right, rightmost
        for (int val : values) {
            container.add(val);
        }

        auto it = container.getMiddleOutOrder();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }

    SUBCASE("Odd number of elements") {
        std::vector<int> values = {1, 2, 3, 4, 5};
        std::vector<int> expected = {3, 2, 4, 1, 5};  // middle, left, right, leftmost, rightmost
        for (int val : values) {
            container.add(val);
        }

        auto it = container.getMiddleOutOrder();
        size_t i = 0;
        for (const auto& val : it) {
            CHECK(val == expected[i++]);
        }
        CHECK(i == expected.size());
    }
}

TEST_CASE("Container with Different Types") {
    SUBCASE("String container") {
        MyContainer<std::string> container;
        container.add("hello");
        container.add("world");
        CHECK(container.size() == 2);
        CHECK(container[0] == "hello");
        CHECK(container[1] == "world");
    }

    SUBCASE("Double container") {
        MyContainer<double> container;
        container.add(1.5);
        container.add(2.7);
        CHECK(container.size() == 2);
        CHECK(container[0] == 1.5);
        CHECK(container[1] == 2.7);
    }
}

TEST_CASE("Edge Cases") {
    MyContainer<int> container;

    SUBCASE("Adding many elements") {
        for (int i = 0; i < 1000; ++i) {
            container.add(i);
        }
        CHECK(container.size() == 1000);
        for (int i = 0; i < 1000; ++i) {
            CHECK(container[i] == i);
        }
    }

    SUBCASE("Removing all elements") {
        container.add(1);
        container.add(2);
        container.remove(1);
        container.remove(2);
        CHECK(container.size() == 0);
        CHECK_THROWS_AS(container[0], std::out_of_range);
    }

    SUBCASE("Multiple identical elements") {
        container.add(1);
        container.add(1);
        container.add(1);
        CHECK(container.size() == 3);
        container.remove(1);
        CHECK(container.size() == 2);
    }
}