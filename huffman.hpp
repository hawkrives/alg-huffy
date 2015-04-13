#ifndef _HUFFY_AND_PUFFY_
#define _HUFFY_AND_PUFFY_ true

#include <iostream>
using std::cerr;
using std::endl;
using std::ostream;
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <algorithm>
using std::stable_sort;
#include <set>
using std::set;
#include <utility>
using std::pair;
using std::make_pair;

#include "ostream.hpp"
#include "join.hpp"

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
	Node(pair<int, int> initial) : data(initial) {};
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

void explore(const Node* start, vector<int> &path, set<pair<vector<int>, int>> &visited, int depth = 0) {
	// cerr << string(depth * 2, ' ') << start << endl;

	if (start->left_child == nullptr && start->right_child == nullptr) {
		visited.insert({path, start->data.value});
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

Node* build_tree(vector<Node*> &queue) {
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

	return nodes.back();
}

void encode(map<int, int> freqs, const vector<int> input) {
	// prepare
	vector<Node*> queue;
	for (auto freq : freqs)
		queue.push_back(new Node(freq));
	Node* head = build_tree(queue);

	// explore
	vector<int> path;
	set<pair<vector<int>, int>> visited;
	explore(head, path, visited);

	// encode
	map<string, int> codes;
	map<int, string> reversed_codes;
	for (auto item : visited) {
		codes.insert({join("", item.first), item.second});
		reversed_codes.insert({item.second, join("", item.first)});
	}
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto pair : codes) {
		cout << comma << pair.first << ":" << pair.second;
		comma[0] = ',';
	}
	cout << endl;
	for (const auto item : input)
		cout << reversed_codes[item];
}

void decode(string input, const map<string, int> codes) {
	string output;
	string to_check = "";
	for (auto inp : input) {
		to_check += inp;
		for (auto code : codes) {
			if (to_check == code.first) {
				output += code.second;
				to_check.clear();
			}
		}		
	}
	cout << output;
}

#endif // _HUFFY_AND_PUFFY_
