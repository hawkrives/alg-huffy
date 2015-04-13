CXX := g++
CXXFLAGS := -Wall --std=c++11 -Wno-missing-braces

encode: encode.cpp huffman.hpp ostream.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

decode: decode.cpp huffman.hpp ostream.hpp split.hpp join.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

huffman.hpp: split.hpp join.hpp ostream.hpp
	@echo

test: encode decode
	./encode < test.txt > test.out
	./decode < test.out > out.txt
	diff test.txt out.txt

clean:
	rm -f encode decode *.o

.PHONY: clean test
