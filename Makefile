CXX := g++
CXXFLAGS := -Wall -g --std=c++11

huffy: huffy.cpp

test: huffy
	./$<

clean:
	rm -f huffy *.o

.PHONY: clean test
