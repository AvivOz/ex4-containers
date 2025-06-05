# author: avivoz4@gmail.com

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Pedantic
INCLUDE = -I./include

.PHONY: all clean test Main valgrind

all: test Main

Main: src/Demo.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) src/Demo.cpp -o Demo

test: test/TestMyContainer.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) test/TestMyContainer.cpp -o test_runner
	./test_runner

valgrind: Main
	valgrind --leak-check=full --show-leak-kinds=all ./Demo

clean:
	rm -f Demo test_runner