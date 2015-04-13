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
#include "split.hpp"
#include "join.hpp"

int main(int argc, char const *argv[]) {
	char next;

	string first_line;
	while (cin.get(next)) {
		if (next == '\n')
			break;
		first_line += next;
	}

	vector<string> code_pairs = split(first_line, ", ");
	map<string, int> codes;
	for (string pair : code_pairs) {
		vector<string> code_to_val = split(pair, ":");
		codes.insert({code_to_val.at(0), stoi(code_to_val.at(1))});
	}

	vector<bool> input_data;
	while (cin.get(next)) {
		input_data.push_back(next == '1' ? 1 : 0);
	}

	string to_decode = join("", input_data);
	decode(to_decode, codes);

	// encode(frequency_data, input_data);

	return 0;
}
