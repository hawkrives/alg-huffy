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
using std::make_pair;
using std::bitset;
#include <algorithm>
using std::sort;
using std::stable_sort;
#include <set>
using std::set;

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

template<typename T>
ostream& operator<<(ostream& s, const set<T>& v) {
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

struct freq_pair {
	int value = -1;
	int frequency = 0;

	freq_pair() {}
	freq_pair(pair<int, int> initial) : value(initial.first), frequency(initial.second) {}

	bool operator== (const freq_pair &rhs) const {
		return value == rhs.value && frequency == rhs.frequency;
		// return this == &rhs;
	}
};

freq_pair operator+ (const freq_pair &lhs, const freq_pair &rhs) {
	freq_pair x;
	// x.value = lhs.value + rhs.value;
	x.frequency = lhs.frequency + rhs.frequency;
	return x;
}

ostream& operator<<(ostream& s, const freq_pair& v) {
	s << "(" << v.value << ", " << v.frequency << ")";
	return s;
}

typedef pair<int, int> pair_int;
typedef vector<pair_int> v_pair_int;

struct Node {
	Node* left_child = nullptr;
	Node* right_child = nullptr;
	freq_pair data = make_pair(-1, 0);

	Node() {};
	Node(int freq, int val) : data({freq, val}) {};
	Node(freq_pair initial) : data(initial) {};
};

// ostream& operator<<(ostream& s, const Node& v) {
// 	s << "{";
// 	s << "key: " << v.data.value << ", ";
// 	s << "frequency: " << v.data.frequency << ", ";
// 	s << "left: " << (*v.left_child).data.value << ", ";
// 	s << "right: " << (*v.right_child).data.value;
// 	return s << "}";
// }

ostream& operator<<(ostream& s, const Node* v) {
	s << "{";
	s << "(" << v->data.value << ",";
	s << v->data.frequency << "), ";
	if (v->left_child != nullptr)
		s << "<: " << v->left_child->data << " " << &v->left_child->data << ", ";
	if (v->right_child != nullptr)
		s << ">: " << v->right_child->data << " " << &v->right_child->data << ", ";
	return s << "}";
}

int is_in_tree(const freq_pair looking_for, const vector<Node*> nodes, int skip_index = 0) {
	for (int i = 0; i < nodes.size(); i++)
		if (i != skip_index)
			if (nodes.at(i)->data == looking_for)
				return i;
	return -1;
}

void explore(const Node* start, vector<bool> &path, set<vector<bool>> &visited, int depth = 0) {
	cout << string(depth * 2, ' ') << start << endl;

	if (start->left_child == nullptr && start->right_child == nullptr) {
		visited.insert(path);
	}

	if (start->left_child != nullptr) {
		path.push_back(0);
		explore(start->left_child, path, visited, depth + 1);
		path.pop_back();
	}
	if (start->right_child != nullptr) {
		path.push_back(1);
		explore(start->right_child, path, visited, depth + 1);
		path.pop_back();
	}
}

vector<Node*> encode(vector<freq_pair> freqs, const vector<int> input) {
	stable_sort(freqs.begin(), freqs.end(), [](const freq_pair a, const freq_pair b) {
		return a.frequency > b.frequency;
	});

	vector<Node*> nodes;
	while (freqs.size() >= 2) {
		cout << "1 " << freqs << endl;
		cout << "1 " << nodes << endl;

		freq_pair bottom = freqs.back();
		freqs.pop_back();
		freq_pair next_bottom = freqs.back();
		freqs.pop_back();

		// cout << "2 " << freqs << endl;
		// cout << "2 " << nodes << endl;

		int bottom_index = is_in_tree(bottom, nodes);
		int next_bottom_index = is_in_tree(next_bottom, nodes, bottom_index);
		if (bottom_index < 0 && next_bottom_index < 0) {
			// if neither of the two lowest nodes are in the tree
			Node *parent = new Node();
			parent->data.frequency = bottom.frequency + next_bottom.frequency;
			parent->data.value = -1;
			parent->left_child = new Node(bottom);
			parent->right_child = new Node(next_bottom);
			freqs.push_back(parent->data);

			nodes.push_back(parent->left_child);
			nodes.push_back(parent->right_child);
			nodes.push_back(parent);
		}
		else if (bottom_index < 0 && next_bottom_index >= 0) {
			// if only the second-lowest frequency node is in the tree
			Node *parent = new Node();
			parent->data.frequency = bottom.frequency + next_bottom.frequency;
			parent->data.value = -1;
			parent->left_child = new Node(bottom);
			parent->right_child = nodes.at(next_bottom_index);
			freqs.push_back(parent->data);

			nodes.push_back(parent->left_child);
			nodes.push_back(parent);
		}
		else if (bottom_index >= 0 && next_bottom_index < 0) {
			// if only the lowest frequency node is in the tree
			Node *parent = new Node();
			parent->data.frequency = bottom.frequency + next_bottom.frequency;
			parent->data.value = -1;
			parent->left_child = nodes.at(bottom_index);
			parent->right_child = new Node(next_bottom);
			freqs.push_back(parent->data);

			nodes.push_back(parent->right_child);
			nodes.push_back(parent);
		}
		else {
			// if both are in the tree
			Node *parent = new Node();
			parent->data.frequency = bottom.frequency + next_bottom.frequency;
			parent->data.value = -1;
			parent->left_child = nodes.at(bottom_index);
			parent->right_child = nodes.at(next_bottom_index);
			freqs.push_back(parent->data);

			nodes.push_back(parent);
		}

		cout << "3 " << freqs << endl;
		cout << "3 " << nodes << endl;

		stable_sort(freqs.begin(), freqs.end(), [](const freq_pair a, const freq_pair b) {
			return a.frequency > b.frequency;
		});

		cout << "4 " << freqs << endl;
		cout << "4 " << nodes << endl;
		cout << endl;

		// cout << nodes << endl;
	}

	vector<bool> path;
	set<vector<bool>> visited;
	explore(nodes.back(), path, visited);

	cout << visited << endl;

	return nodes;
}


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
