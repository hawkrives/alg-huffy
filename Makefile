CXX := g++
CXXFLAGS := -Wall --std=c++11 -Wno-missing-braces

huffy: huffy.cpp

test: huffy
	./$< < test.txt

clean:
	rm -f huffy *.o

.PHONY: clean test
