#ifndef __hmr_ostream__
#define __hmr_ostream__ true

#include <ostream>
using std::ostream;
using std::basic_ostream;
using std::endl;
#include <utility>
using std::pair;
#include <vector>
using std::vector;
#include <map>
using std::map;
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

// A printer for maps
template<typename Key, typename T, typename Compare, typename Allocator>
ostream& operator<<(ostream& stream, const map<Key, T, Compare, Allocator>& map) {
	stream << '{';
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto& pair : map) {
		stream << comma;
		stream << pair.first;
		stream << ':';
		stream << pair.second;
		comma[0] = ',';
	}
	stream << '}';
	return stream;
}

#endif // __hmr_ostream__
