// author: avivoz4@gmail.com    

#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

namespace container {

    template<typename T = int>
    class MyContainer {

        std::vector<T> elements;

    public:
        void add(const T& value) {
            elements.push_back(value);
        }

        void remove(const T& value) {
            auto it = std::remove(elements.begin(), elements.end(), value);
            if (it == elements.end()) {
                throw std::runtime_error("Element not found");
            }
            elemnts.erase(it, elements.end());
        }

        size_t size() const { return elements.size(); }

        friend std::osstream& operator<<(std::osstream& os, const MyContainer& c) {
            for (const auto& e : c.elements) os << e << ' ';
            return os;
        }







    }


















}