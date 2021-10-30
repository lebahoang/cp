#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <utility>
using namespace std;
using ll = long long;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out

void solve(int n, int k) {
    string yes = "YES";
    string no = "NO";
    vector<int> a = {};
    if (k == 0) {
        printf("%s\n", yes.c_str());
        printf("%d\n", 0);
        return;
    }
    int cnt = 1;
    int i = 1;
    int j = i + (1 << (cnt-1)) - 1;
    while (j < n) {
        a.push_back(i);
        if (j > k) {
            i = k+1;
            k = j-i+1;
        } else {
            i = j+1;
        }
        cnt++;
        j = i + (1 << (cnt-1)) - 1;
    }
    if (j == n) {
        a.push_back(i);
        printf("%s\n", yes.c_str());
        printf("%d\n", (int)a.size());
        for (int& x: a) printf("%d\n", x);
    } else {
        printf("%s\n", no.c_str());
    }
}

int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n, k;
        cin >> n >> k;
        solve(n, k);
    }
    return 0;
}