# MyContainer - Generic Container with Multiple Iteration Orders

## Overview
MyContainer is a generic C++ container implementation that supports multiple iteration patterns through specialized iterators. The container is designed for any comparable type and provides efficient traversal in six different orders.

## Project Structure
```
ex4-containers/
├── include/
│   └── MyContainer.hpp     # Main container implementation with iterators
├── tests/
│   ├── doctest.h          # Testing framework header
│   └── TestMyContainer.cpp # Test suite for container and iterators
├── main.cpp               # Main program demonstration
├── Makefile              # Build configuration
└── README.md             # This file
```

## Design Patterns
1. **Iterator Pattern**
   - Each traversal order implements the Iterator pattern
   - Provides uniform interface for different iteration strategies
   - Encapsulates traversal logic within iterator classes

2. **Strategy Pattern**
   - Different iteration orders represent different traversal strategies
   - Allows switching between strategies without changing container code
   - Each strategy is encapsulated in its own iterator class

## Build Instructions

### Requirements
- C++17 or later
- g++ compiler
- STL support
- Elements must be comparable (<, >, ==)

### Compilation Flags
```bash
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic
```

### Build Commands
```bash
make all          # Build both main program and tests
make main         # Build only main program
make test         # Build only tests
make run          # Run main program
make run-all      # Run both main and tests
make clean        # Clean build files
```

### Memory Leak Check
```bash
make valgrind         # Check main program for memory leaks
make valgrind-test    # Check tests for memory leaks
```

## Features
### Container Operations
- Add elements
- Remove elements
- Random access
- Size query

### Iteration Orders
- Regular Order (as inserted)
- Reverse Order (reverse of insertion)
- Ascending Order (smallest to largest)
- Descending Order (largest to smallest)
- Side Cross Order (alternating min/max)
- Middle Out Order (from middle outwards)

## Time Complexities
### Container Operations
- Construction: `O(1)`
- Element Addition: `O(1)` amortized
- Element Removal: `O(n)`
- Random Access: `O(1)`
- Size Query: `O(1)`

### Iterator Construction
- Regular/Reverse Order: `O(1)`
- Ascending/Descending Order: `O(n log n)`
- Side Cross Order: `O(n log n)`
- Middle Out Order: `O(n)`

## Testing
The project uses the doctest framework for unit testing. Tests are located in `tests/TestMyContainer.cpp`.

## Author
Aviv Oz (avivoz4@gmail.com)

## Last Updated
2025-06-07