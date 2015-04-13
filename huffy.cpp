#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::basic_ostream;
using std::ostream;
using std::basic_string;
using std::string;
#include <fstream>
using std::ifstream;
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

// A printer for maps
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
	}
};

ostream& operator<<(ostream& s, const freq_pair& v) {
	s << "(" << v.value << ", " << v.frequency << ")";
	return s;
}

struct Node {
	Node* left_child = nullptr;
	Node* right_child = nullptr;
	freq_pair data = make_pair(-1, 0);

	bool operator== (const Node &rhs) const {
		return left_child == rhs.left_child && right_child == rhs.right_child && data == rhs.data;
	}

	Node() {};
	Node(int freq, int val) : data({freq, val}) {};
	Node(freq_pair initial) : data(initial) {};
};

ostream& operator<<(ostream& s, const Node& n) {
 	s << "{";
 	s << "data: " << n.data;
	if (n.left_child != nullptr) {
		s << ", left: ";
		s << n.left_child->data;
	}
	if (n.right_child != nullptr) {
		s << ", right: ";
		s << n.right_child->data;
	}
 	return s << "}";
 }

ostream& operator<<(ostream& s, const Node* n) {
	return s << *n;
}

int in_tree(const Node* looking_for, const vector<Node*> nodes, int skip_index = 0) {
	for (int i = 0; i < nodes.size(); i++)
		if (i != skip_index && nodes.at(i) == looking_for)
			return i;
	return -1;
}

void explore(const Node* start, vector<bool> &path, set<vector<bool>> &visited, int depth = 0) {
	cerr << string(depth * 2, ' ') << start << endl;

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
	vector<Node*> queue;
	for (auto freq : freqs) {
		queue.push_back(new Node(freq));
	}

	vector<Node*> nodes;
	while (queue.size() >= 2) {
		stable_sort(queue.begin(), queue.end(), [](const Node* a, const Node* b) {
			return a->data.frequency < b->data.frequency;
		});

		Node* bottom = queue.front();
		queue.erase(queue.begin());
		Node* next_bottom = queue.front();
		queue.erase(queue.begin());

		int bottom_index = in_tree(bottom, nodes);
		int next_bottom_index = in_tree(next_bottom, nodes, bottom_index);

		if (bottom_index < 0 && next_bottom_index < 0) {
			// if neither of the two lowest nodes are in the tree
			Node *parent = new Node();
			parent->data.frequency = bottom->data.frequency + next_bottom->data.frequency;
			parent->data.value = -1;
			parent->left_child = bottom;
			parent->right_child = next_bottom;
			queue.push_back(parent);

			nodes.push_back(parent);
		}
		else if (bottom_index < 0 && next_bottom_index >= 0) {
			// if only the second-lowest frequency node is in the tree
			Node *parent = new Node();
			parent->data.frequency = bottom->data.frequency + next_bottom->data.frequency;
			parent->data.value = -1;
			parent->left_child = bottom;
			parent->right_child = nodes.at(next_bottom_index);
			queue.push_back(parent);

			nodes.push_back(parent);
			nodes.erase(nodes.begin() + next_bottom_index);
		}
		else if (bottom_index >= 0 && next_bottom_index < 0) {
			// if only the lowest frequency node is in the tree
			Node *parent = new Node();
			parent->data.frequency = bottom->data.frequency + next_bottom->data.frequency;
			parent->data.value = -1;
			parent->left_child = nodes.at(bottom_index);
			parent->right_child = next_bottom;
			queue.push_back(parent);

			nodes.push_back(parent);
			nodes.erase(nodes.begin() + bottom_index);
		}
		else {
			// if both are in the tree
			Node *parent = new Node();
			parent->data.frequency = bottom->data.frequency + next_bottom->data.frequency;
			parent->data.value = -1;
			parent->left_child = nodes.at(bottom_index);
			parent->right_child = nodes.at(next_bottom_index);
			queue.push_back(parent);

			nodes.push_back(parent);
			nodes.erase(nodes.begin() + bottom_index);
			nodes.erase(nodes.begin() + next_bottom_index);
		}
	}

	vector<bool> path;
	set<vector<bool>> visited;
	explore(nodes.back(), path, visited);

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
