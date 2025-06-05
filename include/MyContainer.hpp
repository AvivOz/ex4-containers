// author: avivoz4@gmail.com

/**
 * @file MyContainer.hpp
 * @brief A generic container implementation with multiple iteration orders
 * @author Aviv Oz
 * @date 2025-06-05
 * @email avivoz4@gmail.com
 * 
 * This container implements a dynamic collection for comparable types
 * with six different iteration orders:
 * - Regular order (as inserted)
 * - Reverse order (reverse of insertion order)
 * - Ascending order (smallest to largest)
 * - Descending order (largest to smallest)
 * - Side cross order (alternating between smallest and largest)
 * - Middle out order (from middle outwards)
 */

#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <ostream>

namespace containers {

    /**
     * @brief Generic container class for comparable types
     * @tparam T The type of elements to store (must be comparable)
     */
    template<typename T>
    class MyContainer {
        std::vector<T> elements;  ///< Internal storage for elements

    public:
        /**
         * @brief Adds a new element to the container
         * @param value The value to add
         * Time Complexity: O(1) amortized
         */
        void add(const T& value) {
            elements.push_back(value);
        }


        /**
         * @brief Removes the first occurrence of an element
         * @param value The value to remove
         * @throws std::runtime_error if the element is not found
         * Time Complexity: O(n) where n is the container size
         */
        void remove(const T& value) {
            auto it = std::find(elements.begin(), elements.end(), value);
            if (it == elements.end()) {
                throw std::runtime_error("Element not found");
            }
            elements.erase(it);
        }

        /**
         * @brief Returns the current size of the container
         * @return Number of elements in the container
         * Time Complexity: O(1)
         */
        size_t size() const {
            return elements.size();
        }

        /**
         * @brief Access operator for the container
         * @param index The index to access
         * @return Reference to the element at the specified index
         * @throws std::out_of_range if index is invalid
         * Time Complexity: O(1)
         */
        T& operator[](size_t index) {
            if (index >= elements.size()) {
                throw std::out_of_range("Index out of bounds");
            }
            return elements[index];
        }

        /**
         * @brief Const access operator for the container
         * @param index The index to access
         * @return Const reference to the element at the specified index
         * @throws std::out_of_range if index is invalid
         * Time Complexity: O(1)
         */
        const T& operator[](size_t index) const {
            if (index >= elements.size()) {
                throw std::out_of_range("Index out of bounds");
            }
            return elements[index];
        }

        /**
         * @brief Output stream operator
         * @param os Output stream
         * @param container Container to output
         * @return Reference to the output stream
         * Time Complexity: O(n)
         */
        friend std::ostream& operator<<(std::ostream& os, const MyContainer& container) {
            os << "[";
            for (size_t i = 0; i < container.size(); ++i) {
                os << container[i];
                if (i < container.size() - 1) os << ",";
            }
            os << "]";
            return os;
        }

        // Iterator Classes

        /**
         * @brief Regular order iterator
         * Iterates through elements in their original insertion order
         * Example: For container [1,4,2,3], iteration order is 1,4,2,3
         */
        class Order {
        private:
            const MyContainer* container; ///< Pointer to the container being iterated
            size_t current;               ///< Current position in the container
        
        public:
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             */
            explicit Order(const MyContainer* c) : container(c), current(0) {}

            /**
             * @brief Inequality comparison operator
             * @param other Another iterator to compare with
             * @return true if iterators are not at the same position
             */
            bool operator!=(const Order& other) const {
                return current != other.current;
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             */
            const T& operator*() const {
                return (*container)[current];
            }
        

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             */
            Order& operator++() {
                ++current;
                return *this;
            }

            /**
             * @brief Get iterator to the beginning
             * @return Iterator pointing to the first element
             */
            Order begin() const { 
                return Order(container); 
            }

            /**
             * @brief Get iterator to the end
             * @return Iterator pointing one past the last element
             */
            Order end() const {
                Order end_it(container);
                end_it.current = container->size();
                return end_it;
            }
        };

        /**
         * @brief Reverse order iterator
         * Iterates through elements in reverse of insertion order
         * Example: For container [1,4,2,3], iteration order is 3,2,4,1
         */
        class ReverseOrder {
            private:
                const MyContainer* container; ///< Pointer to the container being iterated
                size_t current;               ///< Current position in the container

            public:
                /**
                 * @brief Constructor
                 * @param c Pointer to the container to iterate over
                 */
                explicit ReverseOrder(const MyContainer* c) : 
                    container(c),
                    current(c->size() > 0 ? c->size() - 1 : 0) {}


                /**
                 * @brief Inequality comparison operator
                 * @param other Another iterator to compare with
                 * @return true if iterators are not at the same position
                 */
                bool operator!=(const ReverseOrder& other) const {
                    return current != other.current;
                }

                /**
                 * @brief Dereference operator
                 * @return Const reference to the current element
                 */
                const T& operator*() const {
                    return (*container)[current];
                }

                /**
                 * @brief Pre-increment operator (moves backwards)
                 * @return Reference to this iterator after decrementing
                 */
                ReverseOrder& operator++() {
                    if (current > 0) --current;
                    return *this;
                }

                /**
                 * @brief Get iterator to the beginning (end of container)
                 * @return Iterator pointing to the last element
                 */
                ReverseOrder begin() const { 
                    return ReverseOrder(container); 
                }

                /**
                 * @brief Get iterator to the end (start of container)
                 * @return Iterator pointing before the first element
                 */
                ReverseOrder end() const {
                    ReverseOrder end_it(container);
                    end_it.current = static_cast<size_t>(-1);
                    return end_it;
                }
        };

        /**
         * @brief Ascending order iterator
         * Iterates through elements from smallest to largest
         * Example: For container [4,1,3,2], iteration order is 1,2,3,4
         */
        class AscendingOrder {
        private:
            const MyContainer* container;       ///< Pointer to the container being iterated
            std::vector<size_t> sorted_indices; ///< Indices sorted by element values
            size_t current;                     ///< Current position in sorted_indices

        public:
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             */
            explicit AscendingOrder(const MyContainer* c) : container(c), current(0) {
                sorted_indices.resize(c->size());
                for (size_t i = 0; i < c->size(); ++i) {
                    sorted_indices[i] = i;
                }
                std::sort(sorted_indices.begin(), sorted_indices.end(),
                    [c](size_t i1, size_t i2) {
                        return (*c)[i1] < (*c)[i2];
                    });
            }

            /**
             * @brief Inequality comparison operator
             * @param other Another iterator to compare with
             * @return true if iterators are not at the same position
             */
            bool operator!=(const AscendingOrder& other) const {
                return current != other.current;
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             */
            const T& operator*() const {
                return (*container)[sorted_indices[current]];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             */
            AscendingOrder& operator++() {
                ++current;
                return *this;
            }

            /**
             * @brief Get iterator to the beginning (smallest element)
             * @return Iterator pointing to the smallest element
             */
            AscendingOrder begin() const { 
                return AscendingOrder(container); 
            }

             /**
             * @brief Get iterator to the end
             * @return Iterator pointing past the largest element
             */
            AscendingOrder end() const {
                AscendingOrder end_it(container);
                end_it.current = container->size();
                return end_it;
            }
        };

        /**
         * @brief Descending order iterator
         * Iterates through elements from largest to smallest
         * Example: For container [4,1,3,2], iteration order is 4,3,2,1
         */
        class DescendingOrder {
        private:
            const MyContainer* container;        ///< Pointer to the container being iterated
            std::vector<size_t> sorted_indices; ///< Indices sorted by element values
            size_t curren;                      ///< Current position in sorted_indices

        punlic:
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             */
            explicit DescendingOrder(const MyContainer* c) : container(c), current(0) {
                sorted_indices.resize(c->size());
                for (size_t i = 0; i < c->size(); ++i) {
                    sorted_indices[i] = i;
                }
                std::sort(sorted_indices.begin(), sorted_indices.end(),
                    [c](size_t i1, size_t i2) {
                        return (*c)[i1] > (*c)[i2];
                    });
            }
            
             /**
             * @brief Inequality comparison operator
             * @param other Another iterator to compare with
             * @return true if iterators are not at the same position
             */
            bool operator!=(const DescendingOrder& other) const {
                return current != other.current;
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             */
            const T& operator*() const {
                return (*container)[sorted_indices[current]];
            }

             /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             */
            DescendingOrder& operator++() {
                ++current;
                return *this;
            }

            /**
             * @brief Get iterator to the beginning (largest element)
             * @return Iterator pointing to the largest element
             */
            DescendingOrder begin() const { 
                return DescendingOrder(container); 
            }

             /**
             * @brief Get iterator to the end
             * @return Iterator pointing past the smallest element
             */
            DescendingOrder end() const {
                DescendingOrder end_it(container);
                end_it.current = container->size();
                return end_it;
            }
        };
        
        /**
         * @brief Side cross order iterator
         * Iterates alternating between smallest and largest remaining elements
         * Example: For container [4,1,3,2], iteration order is 1,4,2,3
         */
        class SideCrossOrder {
        private:
            const MyContainer* container; ///< Pointer to the container being iterated
            std::vector<size_t> indices;  ///< Pre-calculated iteration order
            size_t current;               ///< Current position in indices

        public: 
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             */
            explicit SideCrossOrder(const MyContainer* c) : container(c), current(0) {
                std::vector<size_t> sorted_indices(c->size());
                for (size_t i = 0; i < c->size(); ++i) {
                    sorted_indices[i] = i;
                }
                
                std::sort(sorted_indices.begin(), sorted_indices.end(),
                    [c](size_t i1, size_t i2) {
                        return (*c)[i1] < (*c)[i2];
                    });

                indices.reserve(c->size());
                size_t left = 0;
                size_t right = sorted_indices.size() - 1;
                
                while (left <= right) {
                    if (left == right) {
                        indices.push_back(sorted_indices[left]);
                        break;
                    }
                    indices.push_back(sorted_indices[left++]);
                    indices.push_back(sorted_indices[right--]);
                }
            }

            /**
             * @brief Inequality comparison operator
             * @param other Another iterator to compare with
             * @return true if iterators are not at the same position
             */
            bool operator!=(const SideCrossOrder& other) const {
                return current != other.current;
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             */
            const T& operator*() const {
                return (*container)[indices[current]];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             */
            SideCrossOrder& operator++() {
                ++current;
                return *this;
            }

            /**
             * @brief Get iterator to the beginning
             * @return Iterator pointing to the first element in side-cross order
             */
            SideCrossOrder begin() const { 
                return SideCrossOrder(container); 
            }

            /**
             * @brief Get iterator to the end
             * @return Iterator pointing past the last element
             */
            SideCrossOrder end() const {
                SideCrossOrder end_it(container);
                end_it.current = container->size();
                return end_it;
            }
        };

        /**
         * @brief Middle out order iterator
         * Iterates from middle element outward
         * Example: For container [1,2,3,4], iteration order is 2,1,3,4
         */
        class MiddleOutOrder {
        private:
            const MyContainer* container; ///< Pointer to the container being iterated
            std::vector<size_t> indices;  ///< Pre-calculated iteration order
            size_t current;               ///< Current position in indices

        public:
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             */
            explicit MiddleOutOrder(const MyContainer* c) : container(c), current(0) {
                indices.reserve(c->size());
                if (c->size() == 0) return;
                
                size_t mid = c->size() / 2;
                indices.push_back(mid);
                
                for (size_t i = 1; i <= mid; ++i) {
                    if (mid - i >= 0)
                        indices.push_back(mid - i);
                    if (mid + i < c->size())
                        indices.push_back(mid + i);
                }
            }

            /**
             * @brief Inequality comparison operator
             * @param other Another iterator to compare with
             * @return true if iterators are not at the same position
             */
            bool operator!=(const MiddleOutOrder& other) const {
                return current != other.current;
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             */
            const T& operator*() const {
                return (*container)[indices[current]];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             */
            MiddleOutOrder& operator++() {
                ++current;
                return *this;
            }

            /**
             * @brief Get iterator to the beginning
             * @return Iterator pointing to the middle element
             */
            MiddleOutOrder begin() const { 
                return MiddleOutOrder(container); 
            }

            /**
             * @brief Get iterator to the end
             * @return Iterator pointing past the last element
             */
            MiddleOutOrder end() const {
                MiddleOutOrder end_it(container);
                end_it.current = container->size();
                return end_it;
            }
        };

        /**
         * @brief Get iterator for reverse order traversal
         * @return ReverseOrder iterator
         */
        ReverseOrder getReverseOrder() const { return ReverseOrder(this); }

        /**
         * @brief Get iterator for ascending order traversal
         * @return AscendingOrder iterator
         */
        AscendingOrder getAscendingOrder() const { return AscendingOrder(this); }

        /**
         * @brief Get iterator for descending order traversal
         * @return DescendingOrder iterator
         */
        DescendingOrder getDescendingOrder() const { return DescendingOrder(this); }

        /**
         * @brief Get iterator for side-cross order traversal
         * @return SideCrossOrder iterator
         */
        SideCrossOrder getSideCrossOrder() const { return SideCrossOrder(this); }

        /**
         * @brief Get iterator for middle-out order traversal
         * @return MiddleOutOrder iterator
         */
        MiddleOutOrder getMiddleOutOrder() const { return MiddleOutOrder(this); }
    };
}