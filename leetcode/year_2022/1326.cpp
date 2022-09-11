#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>
#include <map>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1326.cpp && ./s.out

using namespace std;
using ll = long long;
ll go(int a, int b, int n, vector<int>& ranges, map<pair<int, int>, ll>& m) {
    if (a < 0 || b > n) {
        return (ll)0;
    }
    if (a >= b) {
        return (ll)0;
    }
    if (m.find({a,b}) != m.end()) {
        return m[{a, b}];
    }
    ll ans = 1e9;
    for (int k = a; k <= b; k++) {
        if (ranges[k] == 0) continue;
        int x = k - ranges[k];
        int y = k + ranges[k];
        ll rs = 0;
        ll t1 = go(a, x, n, ranges, m);
        if (t1 >= 0) rs += t1;
        ll t2 = go(y, b, n, ranges, m);
        if (t2 >= 0) rs += t2;
        // printf("IND %d, A %d X %d T1 %lld, Y %d B %d T2 %lld, RS %lld\n", k, a, x, t1, y, b, t2, rs);
        if (t1 == -1 || t2 == -1) continue;
        ans = min(ans, rs+1);
    }
    // printf("A %d B %d ans %lld\n", a, b, ans);
    if (ans == 1e9) {
        m[{a, b}] = -1;
        return -1;
    }
    m[{a, b}] = ans;
    return ans;
}
int solve(int n, vector<int>& ranges) {
    map<pair<int, int>, ll> m;
    return (int)go(0, n, n, ranges, m);
}
int solve1(int n, vector<int>& ranges) {
    vector<pair<int, int>> p = {};
    for (int i = 0; i <= n; i++) {
        p.push_back({max(0, i-ranges[i]), min(n, i+ranges[i])});
    }
    sort(p.begin(), p.end(), [](auto& x, auto& y){
        return x.first < y.first;
    });
    int rs = 0;
    int s = 0;
    int e = -1;
    if (p[0].first > 0) return -1;
    int i = 0;
    while (i <= n && s < n) {
        int eOld = e;
        int iNew = -1;
        for (int j = i; j <= n; j++) {
            if (s >= p[j].first) {
                if (e < p[j].second) {
                    e = p[j].second;
                    iNew = j;
                }
            }
        }
        // printf("S %d E %d iNew %d\n", s, e, iNew);
        if (e == eOld) {
            return -1;
        }
        s = e;
        rs++;
        i = iNew;
    }
    return rs;
}
int main() {
    // int n = 5;
    // vector<int> ranges = {3,4,1,1,0,0};
    // int n = 20;
    // vector<int> ranges = {1,1,1,1,1,1,1,1,1,1,1,1,3,4,5,3,4,5,6,5,7};
    // int n = 10;
    // vector<int> ranges = {1,1,3,4,5,3,4,5,6,5,7};
    // int n = 421;
    // vector<int> ranges = {17,16,10,15,10,13,8,14,2,4,9,11,0,2,7,3,10,3,6,0,1,17,1,0,7,13,17,10,2,15,14,4,4,14,8,16,2,0,9,12,12,3,10,8,6,13,6,0,4,7,4,2,7,4,6,0,17,4,12,15,14,8,7,5,13,7,11,11,14,9,5,9,15,10,8,0,11,5,6,3,12,12,5,8,13,7,4,8,14,0,9,9,4,9,13,5,8,11,9,12,3,3,14,2,12,11,8,2,16,4,0,7,12,2,14,7,0,11,1,5,13,11,11,2,5,7,11,9,4,15,10,1,7,1,2,14,2,16,7,10,2,17,12,12,14,9,0,8,11,8,7,7,15,17,4,8,4,14,3,13,15,5,4,17,11,17,16,7,13,6,2,17,17,12,2,5,13,11,2,14,11,6,4,4,5,9,11,3,5,1,5,15,17,1,1,14,8,7,0,16,6,12,6,3,13,17,10,13,9,16,10,0,4,11,13,12,1,10,3,13,17,5,5,1,3,2,7,3,15,11,0,1,17,1,17,16,12,8,12,11,3,3,11,3,15,13,17,12,13,10,10,0,2,9,7,9,0,6,6,5,5,3,8,0,13,8,0,8,1,1,15,9,15,3,15,14,9,17,9,10,9,13,15,12,3,10,15,7,5,8,6,5,10,3,12,12,4,10,11,2,13,0,15,5,10,11,16,1,2,9,13,13,9,8,2,2,1,17,6,17,16,17,10,9,12,16,8,0,4,16,1,3,0,8,14,0,17,3,5,0,16,3,15,4,3,8,12,2,15,10,9,1,11,12,15,15,3,10,2,7,1,4,15,15,11,1,0,0,0,1,16,16,16,8,13,1,8,6,5,1,5,10,6,15,8,6,3,5,15,3,1,14,0,8,14,14,15,0,8,10,7,2,13,2,1,10,16,16,0,7,5,16,7,1,4,14,6,10,15,13,0,1};

    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distribution(0, 100); // define the range
    int n = 10000;
    vector<int> ranges = {};
    for (int i = 0; i <= n; i++) {
        ranges.push_back(distribution(eng));
    }
    printf("GOGOGO\n");
    printf("%d\n", solve1(n, ranges));
    printf("%d\n", solve(n, ranges));
    return 0;
}