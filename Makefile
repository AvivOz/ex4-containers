# author: avivoz4@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic
INCLUDE = -I./include -I./tests

.PHONY: all clean run test valgrind

all: main test

main: main.cpp include/MyContainer.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) main.cpp -o main

test: tests/TestMyContainer.cpp include/MyContainer.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o test_runner tests/TestMyContainer.cpp

run: main
	./main

run-all: main test
	./main
	./test_runner

valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all ./main

valgrind-test: test
	valgrind --leak-check=full --show-leak-kinds=all ./test_runner

clean:
	rm -f main test_runner