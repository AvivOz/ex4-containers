// author: avivoz4@gmail.com

/**
 * Main.cpp
 * 
 * This program demonstrates the functionality of the custom container class MyContainer
 * and its various iterators. The container allows storing elements and iterating over them
 * in different orders using specialized iterators.
 * 
 * Iterators demonstrated:
 * 1. Regular Order - Elements in order of insertion
 * 2. Reverse Order - Elements in reverse order of insertion
 * 3. Ascending Order - Elements sorted from smallest to largest
 * 4. Descending Order - Elements sorted from largest to smallest
 * 5. Side Cross Order - Elements alternating between smallest and largest
 * 6. Middle Out Order - Elements starting from middle and moving outwards
 * 
 * @author Aviv Oz
 * @date 2025-06-06 15:46:10
 * @file main.cpp
 */

#include <iostream>
#include "MyContainer.hpp"

using namespace std;
using namespace containers;

template<typename Iterator>
void printWithIterator(const string& orderName, Iterator& it, Iterator& end) {
    cout << orderName << ": ";
    while(it != end) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

int main() {
    MyContainer<int> container;
    
    // Add test elements
    cout << "Adding elements: 3, 1, 5, 2, 4" << endl;
    container.add(3);
    container.add(1);
    container.add(5);
    container.add(2);
    container.add(4);
    
    cout << "\nTesting all iteration orders:\n" << endl;

    // Regular order - should print: 3 1 5 2 4
    auto order = container.order();
    auto it = order.begin();
    auto end = order.end();
    printWithIterator("Regular Order", it, end);

    // Reverse order - should print: 4 2 5 1 3
    auto reverseOrder = container.reverse_order();
    auto revIt = reverseOrder.begin();
    auto revEnd = reverseOrder.end();
    printWithIterator("Reverse Order", revIt, revEnd);

    // Ascending order - should print: 1 2 3 4 5
    auto ascOrder = container.ascending_order();
    auto ascIt = ascOrder.begin();
    auto ascEnd = ascOrder.end();
    printWithIterator("Ascending Order", ascIt, ascEnd);

    // Descending order - should print: 5 4 3 2 1
    auto descOrder = container.descending_order();
    auto descIt = descOrder.begin();
    auto descEnd = descOrder.end();
    printWithIterator("Descending Order", descIt, descEnd);

    // Side cross order - should print: 1 5 2 4 3
    auto crossOrder = container.side_cross_order();
    auto crossIt = crossOrder.begin();
    auto crossEnd = crossOrder.end();
    printWithIterator("Side Cross Order", crossIt, crossEnd);

    // Middle out order - should print: 5 1 2 3 4
    auto middleOrder = container.middle_out_order();
    auto middleIt = middleOrder.begin();
    auto middleEnd = middleOrder.end();
    printWithIterator("Middle Out Order", middleIt, middleEnd);

    return 0;
}