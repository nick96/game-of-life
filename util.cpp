#include "util.h"
#include <string>

using namespace std;

string repeat(const string str, const int n) {
	string buf = str;
	for (int i = 0; i < n - 1; i++) {
		buf += str;
	}
	return buf;
}
