#ifndef __hmr_join__
#define __hmr_join__ true

#include <string>
using std::string;
using std::to_string;
#include <vector>
using std::vector;

string join(string sep, vector<string> coll) {
	string str;
	string comma = "\0";
	for (const auto item : coll) {
		str += comma;
		str += item;
		comma = sep;
	}
	return str;
}

template<typename T>
string join(string sep, vector<T> coll) {
	string str;
	string comma = "\0";
	for (auto item : coll) {
		str += comma;
		str += to_string(item);
		comma = sep;
	}
	return str;
}

template<typename T>
string join(int sep, vector<T> coll) {
	return join(to_string(sep), coll);
}

#endif
