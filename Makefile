CXX := g++
CXXFLAGS := -Wall --std=c++11 -Wno-missing-braces

encode: encode.cpp huffman.hpp ostream.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

decode: decode.cpp huffman.hpp ostream.hpp split.hpp join.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

huffman.hpp: split.hpp join.hpp ostream.hpp
	@echo

test: encode decode
	time ./encode < test.txt > test.huffman
	time ./decode < test.huffman > test.decoded
	diff test.txt test.decoded
	cat test.txt
	cat test.decoded

big: encode decode
	time ./encode < words.txt > words.huffman
	time ./decode < words.huffman > words.decoded
	diff words.txt words.decoded

clean:
	rm -f encode decode *.o *.decoded *.huffman *.out

.PHONY: clean test big
