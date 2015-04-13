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
void print_item(basic_ostream<CharT, Traits>& stream,
	const T& item)
{
  stream << item;
}

// A printer for unordered maps
template<typename Key, typename T, typename Compare, typename Allocator>
ostream& operator<<(ostream& stream,
    const map<Key, T, Compare, Allocator>& map)
{
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
	Node *left_child;
	Node *right_child;
	int value = -1;

	Node() {}
	Node(pair<int, int> data) {
		value = data.first;
	}
};

array<pair<int, int>, 2> two_highest_frequencies(const pair_int input) {
	if (input.size() == 0)
		return {};
	else if (input.size() == 1)
		return {input.at(0)};
	return {
		input.at(0),
		input.at(1),
	};
}

void encode(pair_int input) {
	// find two lowest freqs
	auto top_two = two_highest_frequencies(paired_data);
	auto highest = top_two[0];
	auto next_highest = top_two[1];

	// put at the bottom of tree
	Node* parent = new Node();
	parent.left = new Node(lowest);
	parent.right = new Node(next_lowest);

	// add freqs together to find freq of parent node


	// insert parent node into list of freqs
}

int main(int argc, char const *argv[]) {
	char next;
	map<int, int> frequency_data;
	vector<int> input_data;

	while (cin >> next) {
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

	cout << input_data << endl;
	cout << paired_data << endl;

	encode(paired_data);
	return 0;
}
