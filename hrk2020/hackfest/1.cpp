#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>
#include <unordered_map>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 1.cpp && ./s.out < x.txt

using namespace std;
using ll = long long;
int mex(int grundy) {
    if (grundy > 0) return 0;
    return 1;
}
string solve(int n, vector<int> a) {
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++) {
        auto t = m.find(a[i]);
        if (t == m.end()) {
            m[a[i]] = 1;
        } else {
            m[a[i]]++;
        }
    }
    vector<int> dp_grundy(n+4, 0);
    for (int i = 1; i <= n; i++) {
        dp_grundy[i] = mex(dp_grundy[i-1]);
    }
    int nim_sum = -1;
    for (auto t = m.begin(); t != m.end(); t++) {
        int x = dp_grundy[t->second];
        //printf("%d\n", x);
        if (nim_sum == -1) nim_sum = x;
        else nim_sum = nim_sum ^ x;
    }
    if (nim_sum == 0) {
        return "Second";
    }
    return "First";
}

int main() {
    int t;
    cin >> t;
    vector<int> a(100005, 0);
    for (int c = 0; c < t; c++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        printf("%s\n", solve(n, a).c_str());
    }
    return 0;
}
