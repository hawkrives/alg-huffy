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
#include <map>
using std::map;
#include <iomanip>
using std::quoted;

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

// helper function templates for printing each element
template<typename CharT, typename Traits, typename T>
void print_item(basic_ostream<CharT, Traits>& stream,
	const T& item)
{
  stream << item;
}

template<typename CharT, typename Traits, typename Alloc>
void print_item(basic_ostream<CharT, Traits>& stream,
	const basic_string<CharT, Traits, Alloc>& item)
{
  stream << quoted(item);
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

map<int, int> frequency(vector<int> input) {

}

void encode(vector<int> input) {

}

int main(int argc, char const *argv[]) {
	int next;
	vector<int> data;
	while (cin >> next) {
		data.push_back(next);
	}
	cout << data << endl;
	return 0;
}
