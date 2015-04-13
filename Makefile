CXX := g++
CXXFLAGS := -Wall --std=c++11 -Wno-missing-braces

encode: encode.cpp huffman.hpp ostream.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

decode: decode.cpp huffman.hpp ostream.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

test: encode
	./$< < test.txt > test.out

clean:
	rm -f encode decode *.o

.PHONY: clean test
