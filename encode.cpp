#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;

#include "ostream.hpp"
#include "huffman.hpp"

int main(int argc, char const *argv[]) {
	char next;
	map<int, int> frequency_data;
	vector<int> input_data;

	while (cin.get(next)) {
		int val = (int)next;
		input_data.push_back(val);
		if (frequency_data.count(val))
			frequency_data.at(val)++;
		else
			frequency_data.insert({val, 1});
	}

	encode(frequency_data, input_data);

	return 0;
}
