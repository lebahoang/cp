#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <set>
using namespace std;
const int mod = 1e9+7;
// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2.cpp && ./s.out

struct F {
    int s;
    int val;
};
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n;
        cin >> n;
        vector<int> f(n+5, 0);
        vector<vector<int>> nei(n+5, vector<int>{});
        for (int i = 1; i <= n; i++) cin >> f[i];
        int root = 0;
        int x;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            nei[x].push_back(i);
        }
    }
    return 0;
}