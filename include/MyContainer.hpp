// author: avivoz4@gmail.com

/**
 * @file MyContainer.hpp
 * @brief A generic container implementation with multiple iteration orders
 * @author Aviv Oz
 * @date 2025-06-06 15:32:24
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
     * 
     * This container provides efficient storage and multiple iteration patterns
     * for any type that supports comparison operations (<, >, ==).
     * All iterators maintain const-correctness and provide STL-compatible interfaces.
     */
    template<typename T>
    class MyContainer {
    private:
        std::vector<T> elements;  ///< Internal storage for elements

    public:
        /**
         * @brief Default constructor
         * Creates an empty container
         * Time Complexity: O(1)
         */
        MyContainer() = default;

        /**
         * @brief Copy constructor
         * @param other Container to copy from
         * Time Complexity: O(n) where n is the size of other
         */
        MyContainer(const MyContainer& other) = default;

        /**
         * @brief Assignment operator
         * @param other Container to assign from
         * @return Reference to this container
         * Time Complexity: O(n) where n is the size of other
         */
        MyContainer& operator=(const MyContainer& other) = default;

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
         * 
         * Formats the container as [elem1,elem2,...,elemN]
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
         * 
         * This iterator maintains the order in which elements were added to the container.
         * All iterator operations are const and will not modify the container.
         * Time Complexity: O(1) for all operations
         */
        class Order {
        private:
            const MyContainer* container; ///< Pointer to the container being iterated
            size_t current;              ///< Current position in the container
            bool is_end;                 ///< Flag indicating if iterator is at end position

        public:
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             * @param end If true, creates an end iterator
             * Time Complexity: O(1)
             */
            explicit Order(const MyContainer* c, bool end = false) : 
                    container(c), 
                    current(end || c->size() == 0 ? c->size() : 0),
                    is_end(end || c->size() == 0) {}

            /**
             * @brief Copy constructor
             * @param other Iterator to copy from
             * Time Complexity: O(1) for primitive types copy
             */
            Order(const Order& other) = default;

            /**
             * @brief Assignment operator
             * @param other Iterator to assign from
             * @return Reference to this iterator
             * Time Complexity: O(1)
             */
            Order& operator=(const Order& other) {
                if (this != &other) {
                    container = other.container;
                    current = other.current;
                    is_end = other.is_end;
                }
                return *this;
            }

            /**
             * @brief Equality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are at the same position or both at end
             * Time Complexity: O(1)
             */
            bool operator==(const Order& other) const {
                if (is_end && other.is_end) return true;
                if (is_end || other.is_end) return false;
                return current == other.current;
            }     

            /**
             * @brief Inequality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are not at the same position
             * Time Complexity: O(1)
             */
            bool operator!=(const Order& other) const {
                return !(*this == other);
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             * @throws std::out_of_range if iterator is at end or invalid position
             * Time Complexity: O(1)
             */
            const T& operator*() const {
                 if (is_end || current >= container->size()) {
                    throw std::out_of_range("Iterator out of bounds");
                }
                return (*container)[current];
            }
        
            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             * Time Complexity: O(1)
             * 
             * If already at end, remains at end.
             * If increment would go past end, moves to end position.
             */
            Order& operator++() {
                if (!is_end) {
                    ++current;
                    if (current >= container->size()) {
                        is_end = true;
                        current = container->size();
                    }
                }
                return *this;
            }

            /**
             * @brief Post-increment operator
             * @return Copy of iterator before incrementing
             * Time Complexity: O(1)
             */
            Order operator++(int) {
                Order temp = *this;
                ++(*this);
                return temp;
            }

            /**
             * @brief Get iterator to the beginning
             * @return Iterator pointing to the first element
             * Time Complexity: O(1)
             */
            Order begin() const {
                return Order(container, false);
            }

            /**
             * @brief Get iterator to the end
             * @return Iterator pointing one past the last element
             * Time Complexity: O(1)
             */
            Order end() const {
                return Order(container, true);
            }
        };

        /**
         * @brief Reverse order iterator
         * Iterates through elements in reverse of insertion order
         * Example: For container [1,4,2,3], iteration order is 3,2,4,1
         * 
         * This iterator traverses the container from last element to first.
         * All iterator operations are const and will not modify the container.
         * Time Complexity: O(1) for all operations
         */
        class ReverseOrder {
            private:
                const MyContainer* container; ///< Pointer to the container being iterated
                size_t current;              ///< Current position in the container
                bool is_end;                 ///< Flag indicating if iterator is at end position

            public:
                /**
                 * @brief Constructor
                 * @param c Pointer to the container to iterate over
                 * @param end If true, creates an end iterator
                 * Time Complexity: O(1)
                 */
                explicit ReverseOrder(const MyContainer* c, bool end = false) : 
                        container(c), 
                        current(end || c->size() == 0 ? 0 : c->size() - 1),
                        is_end(end || c->size() == 0) {}

                /**
                 * @brief Copy constructor
                 * @param other Iterator to copy from
                 * Time Complexity: O(1) for primitive types copy
                 */
                ReverseOrder(const ReverseOrder& other) = default;

                /**
                 * @brief Assignment operator
                 * @param other Iterator to assign from
                 * @return Reference to this iterator
                 * Time Complexity: O(1)
                 */
                ReverseOrder& operator=(const ReverseOrder& other) {
                    if (this != &other) {
                        container = other.container;
                        current = other.current;
                        is_end = other.is_end;
                    }
                    return *this;
                }

                /**
                 * @brief Equality comparison operator
                 * @param other Iterator to compare with
                 * @return true if iterators are at the same position or both at end
                 * Time Complexity: O(1)
                 */
                bool operator==(const ReverseOrder& other) const {
                    if (is_end && other.is_end) return true;
                    if (is_end || other.is_end) return false;
                    return current == other.current;                
                }

                /**
                 * @brief Inequality comparison operator
                 * @param other Iterator to compare with
                 * @return true if iterators are not at the same position
                 * Time Complexity: O(1)
                 */
                bool operator!=(const ReverseOrder& other) const {
                    return !(*this == other);
                }

                /**
                 * @brief Dereference operator
                 * @return Const reference to the current element
                 * @throws std::out_of_range if iterator is at end or invalid position
                 * Time Complexity: O(1)
                 */
                const T& operator*() const {
                    if (is_end || current >= container->size()) {
                        throw std::out_of_range("Iterator out of bounds");
                    }
                    return (*container)[current];
                }

                /**
                 * @brief Pre-increment operator (moves backwards)
                 * @return Reference to this iterator after decrementing
                 * Time Complexity: O(1)
                 * 
                 * If already at end, remains at end.
                 * If decrement would go past beginning, moves to end position.
                 */
                ReverseOrder& operator++() {
                    if (!is_end) {
                        if (current > 0) {
                            --current;
                        } else {
                            is_end = true;
                            current = 0;  
                        }
                    }
                    return *this;
                }

                /**
                 * @brief Post-increment operator
                 * @return Copy of iterator before incrementing
                 * Time Complexity: O(1)
                 */
                ReverseOrder operator++(int) {
                    ReverseOrder temp = *this;
                    ++(*this);
                    return temp;
                }

                /**
                 * @brief Get iterator to the beginning (end of container)
                 * @return Iterator pointing to the last element
                 * Time Complexity: O(1)
                 */
                ReverseOrder begin() const {
                    return ReverseOrder(container, false);
                }

                /**
                 * @brief Get iterator to the end (start of container)
                 * @return Iterator pointing before the first element
                 * Time Complexity: O(1)
                 */
                ReverseOrder end() const {
                    return ReverseOrder(container, true);
                }
        };

        /**
         * @brief Ascending order iterator
         * Iterates through elements from smallest to largest
         * Example: For container [4,1,3,2], iteration order is 1,2,3,4
         * 
         * This iterator provides sorted access to elements in ascending order.
         * Creates and maintains a sorted index array for efficient iteration.
         * Time Complexity: O(n log n) for construction, O(1) for iteration operations
         */
        class AscendingOrder {
        private:
            const MyContainer* container;       ///< Pointer to the container being iterated
            std::vector<size_t> sorted_indices; ///< Indices sorted by element values
            size_t current;                     ///< Current position in sorted_indices
            bool is_end;                        ///< Flag indicating if iterator is at end position

                    public:
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             * @param end If true, creates an end iterator
             * Time Complexity: O(n log n) where n is container size
             */
            explicit AscendingOrder(const MyContainer* c, bool end = false) : 
                container(c), 
                current(end || c->size() == 0 ? c->size() : 0),
                is_end(end || c->size() == 0) {
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
             * @brief Copy constructor
             * Time Complexity: O(n) for vector copy
             */
            AscendingOrder(const AscendingOrder& other) = default;

            /**
             * @brief Copy constructor
             * @param other Iterator to copy from
             * Time Complexity: O(n) for sorted_indices vector copy
             */
            AscendingOrder& operator=(const AscendingOrder& other) {
                if (this != &other) {
                    container = other.container;
                    current = other.current;
                    is_end = other.is_end;
                    sorted_indices = other.sorted_indices;
                }
                return *this;
            }

            /**
             * @brief Equality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are at the same position or both at end
             * Time Complexity: O(1)
             */
            bool operator==(const AscendingOrder& other) const {
                if (is_end && other.is_end) return true;
                if (is_end || other.is_end) return false;
                return current == other.current;            
            }

            /**
             * @brief Inequality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are not at the same position
             * Time Complexity: O(1)
             */
            bool operator!=(const AscendingOrder& other) const {
                return !(*this == other);
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             * @throws std::out_of_range if iterator is at end or invalid position
             * Time Complexity: O(1)
             */
            const T& operator*() const {
                if (current >= container->size()) {
                    throw std::out_of_range("Iterator out of bounds");
                }
                return (*container)[sorted_indices[current]];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             * Time Complexity: O(1)
             */
            AscendingOrder& operator++() {
                if (!is_end) {
                    ++current;
                    if (current >= container->size()) {
                        is_end = true;
                        current = container->size();
                    }
                }
                return *this;
            }

            /**
             * @brief Post-increment operator
             * @return Copy of iterator before incrementing
             * Time Complexity: O(1)
             */
            AscendingOrder operator++(int) {
                AscendingOrder temp = *this;
                ++(*this);
                return temp;
            }

            /**
             * @brief Get iterator to the beginning (smallest element)
             * @return Iterator pointing to the smallest element
             * Time Complexity: O(n log n) for sorting
             */
            AscendingOrder begin() const {
                return AscendingOrder(container, false);
            }

             /**
             * @brief Get iterator to the end
             * @return Iterator pointing past the largest element
             * Time Complexity: O(1)
             */
            AscendingOrder end() const {
                return AscendingOrder(container, true);
            }
        };

        /**
         * @brief Descending order iterator
         * Iterates through elements from largest to smallest
         * Example: For container [4,1,3,2], iteration order is 4,3,2,1
         * 
         * This iterator provides sorted access to elements in descending order.
         * Creates and maintains a sorted index array for efficient iteration.
         * Time Complexity: O(n log n) for construction, O(1) for iteration operations
         */
        class DescendingOrder {
        private:
            const MyContainer* container;        ///< Pointer to the container being iterated
            std::vector<size_t> sorted_indices; ///< Indices sorted by element values
            size_t current;                     ///< Current position in sorted_indices
            bool is_end;                        ///< Flag indicating if iterator is at end position

        public:
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             * @param end If true, creates an end iterator
             * Time Complexity: O(n log n) where n is container size
             */
            explicit DescendingOrder(const MyContainer* c, bool end = false) : 
                container(c), 
                current(end || c->size() == 0 ? c->size() : 0),
                is_end(end || c->size() == 0) {  
                if (c->size() == 0) return; 
                
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
             * @brief Copy constructor
             * @param other Iterator to copy from
             * Time Complexity: O(n) for vector copy
             */
            DescendingOrder(const DescendingOrder& other) = default;

            /**
             * @brief Copy constructor
             * @param other Iterator to copy from
             * Time Complexity: O(n) for sorted_indices vector copy
             */
            DescendingOrder& operator=(const DescendingOrder& other) {
                if (this != &other) {
                    container = other.container;
                    current = other.current;
                    is_end = other.is_end;
                    sorted_indices = other.sorted_indices;
                }
                return *this;
            }
            
            /**
             * @brief Equality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are at the same position or both at end
             * Time Complexity: O(1)
             */
            bool operator==(const DescendingOrder& other) const {
                if (is_end && other.is_end) return true;
                if (is_end || other.is_end) return false;
                return current == other.current;
            }

            /**
             * @brief Inequality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are not at the same position
             * Time Complexity: O(1)
             */
            bool operator!=(const DescendingOrder& other) const {
                return !(*this == other);
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             * @throws std::out_of_range if iterator is at end or invalid position
             * Time Complexity: O(1)
             */
            const T& operator*() const {
                if (is_end || current >= container->size()) {
                    throw std::out_of_range("Iterator out of bounds");
                }
                return (*container)[sorted_indices[current]];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             * Time Complexity: O(1)
             */
            DescendingOrder& operator++() {
                if (!is_end) {
                    ++current;
                    if (current >= container->size()) {
                        is_end = true;
                        current = container->size();
                    }
                }
                return *this;
            }

            /**
             * @brief Post-increment operator
             * @return Copy of iterator before incrementing
             * Time Complexity: O(1)
             */
            DescendingOrder operator++(int) {
                DescendingOrder temp = *this;
                ++(*this);
                return temp;
            }

            /**
             * @brief Get iterator to the beginning (largest element)
             * @return Iterator pointing to the largest element
             * Time Complexity: O(n log n) for sorting
             */
            DescendingOrder begin() const { 
                return DescendingOrder(container, false); 
            }

            /**
             * @brief Get iterator to the end
             * @return Iterator pointing past the smallest element
             * Time Complexity: O(1)
             */
            DescendingOrder end() const {
                return DescendingOrder(container, true);
            }
        };

        /**
         * @brief Side cross order iterator
         * Iterates alternating between smallest and largest remaining elements
         * Example: For container [4,1,3,2], iteration order is 1,4,2,3
         * 
         * This iterator provides alternating access between minimum and maximum elements.
         * Creates and maintains a pre-calculated traversal order for efficient iteration.
         * Time Complexity: O(n log n) for construction, O(1) for iteration operations
         */
        class SideCrossOrder {
        private:
            const MyContainer* container; ///< Pointer to the container being iterated
            std::vector<size_t> indices;  ///< Pre-calculated iteration order
            size_t current;               ///< Current position in indices
            bool is_end;                  ///< Flag indicating if iterator is at end position

        public: 
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             * @param end If true, creates an end iterator
             * Time Complexity: O(n log n) where n is container size
             */
            explicit SideCrossOrder(const MyContainer* c, bool end = false) : 
                container(c), 
                current(0),
                is_end(end) {
                
                if (c->size() == 0 || end) {
                    is_end = true;
                    return;
                }
                
                std::vector<std::pair<T, size_t>> sorted;
                for (size_t i = 0; i < c->size(); ++i) {
                    sorted.push_back({(*c)[i], i});
                }
                std::sort(sorted.begin(), sorted.end());

                indices.resize(c->size());
                size_t idx = 0;
                size_t left = 0;
                size_t right = sorted.size() - 1;
                
                while (left <= right) {
                    if (left == right) {
                        indices[idx] = sorted[left].second;
                        break;
                    }
                    indices[idx++] = sorted[left++].second;
                    indices[idx++] = sorted[right--].second;
                }
            }

            /**
             * @brief Copy constructor
             * @param other Iterator to copy from
             * Time Complexity: O(n) for indices vector copy
             */
            SideCrossOrder(const SideCrossOrder& other) = default;

            /**
             * @brief Assignment operator
             * @param other Iterator to assign from
             * @return Reference to this iterator
             * Time Complexity: O(n) for vector assignment
             */
            SideCrossOrder& operator=(const SideCrossOrder& other) {
                if (this != &other) {
                    container = other.container;
                    current = other.current;
                    is_end = other.is_end;
                    indices = other.indices;
                }
                return *this;
            }

            /**
             * @brief Equality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are at the same position or both at end
             * Time Complexity: O(1)
             */
            bool operator==(const SideCrossOrder& other) const {
                if (is_end && other.is_end) return true;
                if (is_end || other.is_end) return false;
                return current == other.current;
            }

            /**
             * @brief Inequality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are not at the same position
             * Time Complexity: O(1)
             */
            bool operator!=(const SideCrossOrder& other) const {
                return !(*this == other);
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             * @throws std::out_of_range if iterator is at end or invalid position
             * Time Complexity: O(1)
             */
            const T& operator*() const {
                if (is_end || current >= container->size()) {
                    throw std::out_of_range("Iterator out of bounds");
                }
                return (*container)[indices[current]];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             * Time Complexity: O(1)
             */
            SideCrossOrder& operator++() {
                if (!is_end) {
                    ++current;
                    if (current >= indices.size()) {
                        is_end = true;
                        current = indices.size();
                    }
                }
                return *this;
            }

            /**
             * @brief Post-increment operator
             * @return Copy of iterator before incrementing
             * Time Complexity: O(1)
             */
            SideCrossOrder operator++(int) {
                SideCrossOrder temp = *this;
                ++(*this);
                return temp;
            }

            /**
             * @brief Get iterator to the beginning
             * @return Iterator pointing to the first element in side-cross order
             * Time Complexity: O(n log n) for sorting and preparing indices
             */
            SideCrossOrder begin() const { 
                return SideCrossOrder(container); 
            }

            /**
             * @brief Get iterator to the end
             * @return Iterator pointing past the last element
             * Time Complexity: O(1)
             */
            SideCrossOrder end() const {
                return SideCrossOrder(container, true);
            }
        };

        /**
         * @brief Middle out order iterator
         * Iterates from middle element outward
         * Example: For container [1,2,3,4], iteration order is 2,3,1,4
         * For odd size: middle element first, then alternating left and right
         * For even size: left-middle first, then right-middle, then alternating outward
         * 
         * This iterator provides traversal starting from the middle elements.
         * Creates and maintains a pre-calculated traversal order for efficient iteration.
         * Time Complexity: O(n) for construction, O(1) for iteration operations
         */
        class MiddleOutOrder {
        private:
            const MyContainer* container; ///< Pointer to the container being iterated
            std::vector<size_t> indices;  ///< Pre-calculated iteration order
            size_t current;               ///< Current position in indices
            bool is_end;                  ///< Flag indicating if iterator is at end position

        public:
            /**
             * @brief Constructor
             * @param c Pointer to the container to iterate over
             * @param end If true, creates an end iterator
             * Time Complexity: O(n) for preparing indices
             */
            explicit MiddleOutOrder(const MyContainer* c, bool end = false) : 
                container(c), 
                current(end ? c->size() : 0),
                is_end(end || c->size() == 0) {
                
                if (c->size() == 0) return;

                indices.resize(c->size());
                size_t mid = c->size() / 2;
                size_t index = 0;
                
                // Different handling for even and odd sized containers
                if (c->size() % 2 == 0) {
                    indices[index++] = mid - 1;  // Left middle
                    indices[index++] = mid;      // Right middle
                    
                    // Alternating outward from middle
                    for (size_t i = 1; index < c->size(); ++i) {
                        if (mid - 1 - i >= 0 && index < c->size()) {
                            indices[index++] = mid - 1 - i;
                        }
                        if (mid + i < c->size() && index < c->size()) {
                            indices[index++] = mid + i;
                        }
                    }
                }
                else {
                    indices[index++] = mid;      // Middle element
                    
                    // Alternating left and right from middle
                    for (size_t i = 1; index < c->size(); ++i) {
                        if (mid - i >= 0 && index < c->size()) {
                            indices[index++] = mid - i;
                        }
                        if (mid + i < c->size() && index < c->size()) {
                            indices[index++] = mid + i;
                        }
                    }
                }
            }

            /**
             * @brief Copy constructor
             * @param other Iterator to copy from
             * Time Complexity: O(n) for vector copy
             */
            MiddleOutOrder(const MiddleOutOrder& other) = default;

            /**
             * @brief Copy constructor
             * @param other Iterator to copy from
             * Time Complexity: O(n) for indices vector copy
             */
            MiddleOutOrder& operator=(const MiddleOutOrder& other) {
                if (this != &other) {
                    container = other.container;
                    current = other.current;
                    is_end = other.is_end;
                    indices = other.indices;
                }
                return *this;
            }

            /**
             * @brief Equality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are at the same position or both at end
             * Time Complexity: O(1)
             */
            bool operator==(const MiddleOutOrder& other) const {
                if (is_end && other.is_end) return true;
                if (is_end || other.is_end) return false;
                return current == other.current;
            }

            /**
             * @brief Inequality comparison operator
             * @param other Iterator to compare with
             * @return true if iterators are not at the same position
             * Time Complexity: O(1)
             */
            bool operator!=(const MiddleOutOrder& other) const {
                return !(*this == other);
            }

            /**
             * @brief Dereference operator
             * @return Const reference to the current element
             * @throws std::out_of_range if iterator is at end or invalid position
             * Time Complexity: O(1)
             */
            const T& operator*() const {
                if (is_end || current >= container->size()) {
                    throw std::out_of_range("Iterator out of bounds");
                }
                return (*container)[indices[current]];
            }

            /**
             * @brief Pre-increment operator
             * @return Reference to this iterator after incrementing
             * Time Complexity: O(1)
             */
            MiddleOutOrder& operator++() {
                if (!is_end) {
                    ++current;
                    if (current >= indices.size()) {
                        is_end = true;
                        current = indices.size();
                    }
                }
                return *this;
            }

                        /**
             * @brief Post-increment operator
             * @return Copy of iterator before incrementing
             * Time Complexity: O(1)
             */
            MiddleOutOrder operator++(int) {
                MiddleOutOrder temp = *this;
                ++(*this);
                return temp;
            }

            /**
             * @brief Get iterator to the beginning
             * @return Iterator pointing to the middle element(s)
             * Time Complexity: O(n) for preparing indices
             */
            MiddleOutOrder begin() const {
                return MiddleOutOrder(container);
            }

            /**
             * @brief Get iterator to the end
             * @return Iterator pointing past the last element
             * Time Complexity: O(1)
             */
            MiddleOutOrder end() const {
                return MiddleOutOrder(container, true);
            }
        };

    public:
        /**
         * @brief Get iterator for original insertion order traversal
         * @return Order iterator
         * Time Complexity: O(1)
         */
        Order order() const { return Order(this); }

        /**
         * @brief Get iterator for reverse insertion order traversal
         * @return ReverseOrder iterator
         * Time Complexity: O(1)
         */
        ReverseOrder reverse_order() const { return ReverseOrder(this); }

        /**
         * @brief Get iterator for ascending order traversal
         * @return AscendingOrder iterator
         * Time Complexity: O(n log n)
         */
        AscendingOrder ascending_order() const { return AscendingOrder(this); }

        /**
         * @brief Get iterator for descending order traversal
         * @return DescendingOrder iterator
         * Time Complexity: O(n log n)
         */
        DescendingOrder descending_order() const { return DescendingOrder(this); }

        /**
         * @brief Get iterator for side-cross order traversal
         * @return SideCrossOrder iterator
         * Time Complexity: O(n log n)
         */
        SideCrossOrder side_cross_order() const { return SideCrossOrder(this); }

        /**
         * @brief Get iterator for middle-out order traversal
         * @return MiddleOutOrder iterator
         * Time Complexity: O(n)
         */
        MiddleOutOrder middle_out_order() const { return MiddleOutOrder(this); }
    };
}