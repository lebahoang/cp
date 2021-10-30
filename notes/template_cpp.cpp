#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <string>
#include <queue>
#include <utility>
#include <stack>
#include <map>
#include <unordered_map>

// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out

using namespace std;
void add_map(unordered_map<int, int>& m, int k, int v) {
    if (m.find(k) != m.end()) {
        m[k] += v;
    } else {
        m[k] = v;
    }
}
void pm(string name, unordered_map<int, int>& m) {
    printf("%s ", name.c_str());
    for (auto it = m.begin(); it != m.end(); it++) {
        printf("{%d:%d} ", it->first, it->second);
    }
    printf("\n");
}
void pv(vector<int> v) {
    for (int x: v) {
        printf("%d ", x);
    }
    printf("\n");
}


int main() {
	return 0;
}