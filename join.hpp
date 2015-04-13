#ifndef __hmr_join__
#define __hmr_join__ true

#include <string>
using std::string;
using std::to_string;
#include <vector>
using std::vector;

template<typename T>
string join(string sep, vector<T> coll) {
	string str;
	for (auto item : coll)
		str += to_string(item) + sep;
	return str;
}

#endif
