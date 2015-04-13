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

#include "ostream.h"
#include "huffman.h"

vector<freq_pair> map_to_pairs(const map<int, int> &m) {
	vector<freq_pair> vec;
	vec.reserve(m.size());
	for (auto item : m){
		vec.emplace_back(item);
	}
	return vec;
}

int main(int argc, char const *argv[]) {
	char next;
	map<int, int> frequency_data;
	vector<int> input_data;

	while (cin.get(next)) {
		int val = (int)next;
		input_data.push_back(val);
		if (frequency_data.count(val)) {
			frequency_data.at(val)++;
		}
		else {
			frequency_data.insert({val, 1});
		}
	}

	vector<freq_pair> paired_data = map_to_pairs(frequency_data);

	encode(paired_data, input_data);

	// cout << "freqs: " << frequency_data << endl;
	// cout << "input: " << bin_input << endl;
	// cout << "encoded: " << encoded << endl;

	// auto decoded = decode(encoded, frequency_data);

	return 0;
}
