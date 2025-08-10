CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Itests

all: ufo

ufo: ufo.cpp ufo_functions.cpp
	$(CXX) $(CXXFLAGS) ufo.cpp ufo_functions.cpp -o ufo

# Build tests executable
tests/test_check_guess: tests/test_check_guess.cpp ufo_functions.cpp
	$(CXX) $(CXXFLAGS) tests/test_check_guess.cpp ufo_functions.cpp -o tests/test_check_guess

.PHONY: test clean

test: tests/test_check_guess
	./tests/test_check_guess

clean:
	rm -f ufo tests/test_check_guess
