#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::basic_ostream;
using std::ostream;
using std::basic_string;
using std::string;
#include <vector>
using std::vector;
#include <unordered_map>
using std::unordered_map;
#include <map>
using std::map;
#include <array>
using std::array;
#include <utility>
using std::pair;
using std::bitset;
#include <algorithm>
using std::sort;

template<typename T>
ostream& operator<<(ostream& s, const pair<T, T>& v) {
	s << "(" << v.first << ", " << v.second << ")";
	return s;
}

template<typename T>
ostream& operator<<(ostream& s, const vector<T>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']';
}

template<typename T, size_t N>
ostream& operator<<(ostream& s, const array<T, N>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']';
}

// helper function templates for printing each element
template<typename CharT, typename Traits, typename T>
void print_item(basic_ostream<CharT, Traits>& stream, const T& item) {
	stream << item;
}

// A printer for unordered maps
template<typename Key, typename T, typename Compare, typename Allocator>
ostream& operator<<(ostream& stream, const map<Key, T, Compare, Allocator>& map) {
	stream << '{';
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto& pair : map) {
		stream << comma;
		print_item(stream, pair.first);
		stream << ':';
		print_item(stream, pair.second);
		comma[0] = ',';
	}
	stream << '}';
	return stream;
}

/////

typedef vector<pair<int, int>> pair_int;

struct Node {
	Node* left_child = nullptr;
	Node* right_child = nullptr;
	int data = -1;

	Node() {};
	Node(int initial) : data(initial);
};

vector<string> encode(map<int, int> freqs, vector<int> input) {
	map<int, string> huff;

	int counter = 0;
	for (const auto item : freqs) {
		huff.insert({
			item.first,
			string(counter, '0') + ((counter == freqs.size() - 1) ? "" : "1"),
		});
		counter++;
	}

	vector<string> output;
	for (auto item : input)
		output.push_back(huff.at(item));

	return output;
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

	pair_int paired_data;
	for (auto item : frequency_data) {
		paired_data.push_back(item);
	}

	sort(paired_data.begin(), paired_data.end(), [](const pair<int,int> a, const pair<int,int> b) {
		return a.second > b.second;
	});

	vector<bitset<8>> bin_input;
	for (const auto item : input_data)
		bin_input.push_back(bitset<8>(item));

	auto encoded = encode(frequency_data, input_data);

	cout << "freqs: " << frequency_data << endl;
	cout << "input: " << bin_input << endl;
	cout << "encoded: " << encoded << endl;

	auto decoded = decode(encoded, frequency_data);

	return 0;
}
