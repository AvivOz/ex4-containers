// author: avivoz4@gmail.com    

#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

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
            elements.erase(it, elements.end());
        }

        size_t size() const { return elements.size(); }

        friend std::osstream& operator<<(std::osstream& os, const MyContainer& c) {
            for (const auto& e : c.elements) os << e << ' ';
            return os;
        }

        class Order {
        private:
            const MyContainer* container;
            size_t current;
        
        public:
            Order(const MyContainer* c) : container(c), current(0) {}

            bool operator!=(const Order& other) const {
                return current != other.current;
            }

            T& operator*() {
                return container->elements[current];
            }

            Order& operator++() {
                ++current;
                return *this;
            }

            Order begin() const {
                return Order(container);
            }

            Order end() const {
                return Order(container, container->size());
            }
        };

        class ReverseOrder {
            private:
                const MyContainer* container;
                size_t current;

            public:
                ReverseOrder(const MyContainer* c) : container(c), current(c->size() - 1) {}

                bool operator!=(const ReverseOrder& other) const {
                    return current != other.current;
                }

                T& operator*() {
                    return container->elements[current];
                }

                ReverseOrder& operator++() {
                    --current;
                    return *this;
                }

                ReverseOrder begin() const {
                    return ReverseOrder(container);
                }

                ReverseOrder end() const {
                    return ReverseOrder(container, -1);
                }
        };

        class AscendingOrder {
        private:
            const MyContainer* container;
            std::vector<size_t> sorted_indices;
            size_t current;

        public:
            AscendingOrder(const MyContainer* c) : container(c), current(0) {

                for (size_t i = 0; i < c->size(), i++) {
                    sorted_indices.push_back(i);
                }

                std::sort(sorted_indices.begin(), sorted_indices.end(), [c](size_t i1, size_t i2) {
                    return c->elements[i1] < c->elements[i2]; 
                });
            }

            bool operator!=(const AscendingOrder& other) const {
                return current != other.current;
            }

            T& operator*() {
                return container->elements[sorted_indices[current]];
            }

            AscendingOrder& operator++() {
                ++current;
                return *this;
            }

            AscendingOrder being() const {
                return AscendingOrder(container);
            }

            AscendingOrder end() const {
                auto end_it = AscendingOrder(container);
                end_it.current = container->size();
                return end_it;
            }
        };

        class DescendingOrder {
        private:
            const MyContainer* container;
            std::vector<size_t> sorted_indices;
            size_t curren;

        punlic:
            DescendingOrder(const MyContainer* c) : container(c), current(0) {
                // Create sorted indices
                for (size_t i = 0; i < c->size(); ++i) {
                    sorted_indices.push_back(i);
                }
                std::sort(sorted_indices.begin(), sorted_indices.end(), [c](size_t i1, size_t i2) {
                        return c->elements[i1] > c->elements[i2];
                });
            }
            
            bool operator!=(const DescendingOrder& other) const {
                return != other.current;
            }

            T& operator*() {
                return container->elements[sorted_indices[current]];
            }

            DescendingOrder& operator++() {
                ++current;
                return *this;
            }

            DescendingOrder begin() const {
                return DescendingOrder(container);
            }

            DescendingOrder end() const {
                auto end_it = DescendingOrder(container);
                end_it.current = container->size();
                return end_it;
            }
        };
        
        class SideCrossOrder {
        private:
            const MyContainer* container;
            std::vector<size_t> indices;
            size_t current;

        public: 
            SideCrossOrder(const MyContainer* c) : container(c), current(0) {
                std::vector<T> sorted = c->elements;
                std::sort(sorted.begin(), sorted.end());
                size_t left = 0;
                size_t right = c->size() -1;

                while (left <= right) {
                    indices,push_back(left++);
                    if (left <= right) {
                        indices,push_back(right--);
                    }
                }
            }

            bool operator!=(const SideCrossOrder& other) const {
                return current != other.current;
            }

            T& operator*() {
                return container->elements[indices[current]];
            }

             SideCrossOrder& operator++() {
                ++current;
                return *this;
            }

            SideCrossOrder begin() const {
                return SideCrossOrder(container);
            }

            SideCrossOrder end() const {
                auto end_it = SideCrossOrder(container);
                end_it.current = container->size();
                return end_it;
            }
        };

        class MiddleOutOrder {
        private:
            const MyContainer* container;
            std::vector<size_t> indices;
            size_t current;

        public:
            MiddleOutOrder(const MyContainer* c) : container(c), current(0) {
                size_t mid = c->size() / 2;
                indices.push_back(mid);
                
                for (size_t i = 1; i <= mid; ++i) {
                    if (mid - i >= 0)
                        indices.push_back(mid - i);
                    if (mid + i < c->size())
                        indices.push_back(mid + i);
                }
            }

            bool operator!=(const MiddleOutOrder& other) const {
                return current != other.current;
            }

            T& operator*() {
                return container->elements[indices[current]];
            }

            MiddleOutOrder& operator++() {
                ++current;
                return *this;
            }

            MiddleOutOrder begin() const {
                return MiddleOutOrder(container);
            }

            MiddleOutOrder end() const {
                auto end_it = MiddleOutOrder(container);
                end_it.current = container->size();
                return end_it;
            }
        };

        Order getOrder() const { return Order(this); }
        ReverseOrder getReverseOrder() const { return ReverseOrder(this); }
        AscendingOrder getAscendingOrder() const { return AscendingOrder(this); }
        DescendingOrder getDescendingOrder() const { return DescendingOrder(this); }
        SideCrossOrder getSideCrossOrder() const { return SideCrossOrder(this); }
        MiddleOutOrder getMiddleOutOrder() const { return MiddleOutOrder(this); }
    };
}
