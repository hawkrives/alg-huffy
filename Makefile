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
	time ./decode < test.huffman > out.decoded
	diff test.txt out.decoded
	cat test.txt
	cat out.decoded

big: encode decode
	time ./encode < words > words.huffman
	time ./decode < words.huffman > words.decoded
	diff words words.decoded

clean:
	rm -f encode decode *.o

.PHONY: clean test big
