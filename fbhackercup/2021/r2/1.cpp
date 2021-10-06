#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out
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
void add_map(unordered_map<int, int>& m, int k, int v) {
    if (m.find(k) != m.end()) {
        m[k] += v;
    } else {
        m[k] = v;
    }
}
int solve(int n, int m, vector<vector<int>>& arr) {
    unordered_map<int, int> a = {};
    unordered_map<int, int> b = {};
    for (int j = 0; j < m; j++) {
        if (a.find(arr[0][j]) == a.end()) {
            a[arr[0][j]] = 1;
        } else {
            a[arr[0][j]]++;
        }
    }
    int rs = 0;
    for (int i = 1; i <= n; i++) {
        // pm("A", a);
        // pm("B", b);
        // printf("RS %d\n", rs);
        unordered_map<int, int> na = {};
        unordered_map<int, int> nb = {};
        unordered_map<int, int> x = {};
        for (int j = 0; j < m; j++) {
            if (x.find(arr[i][j]) == x.end()) {
                x[arr[i][j]] = 1;
            } else {
                x[arr[i][j]]++;
            }
        }
        auto it = b.begin();
        while (it != b.end()) {
            int k = it->first;
            int bv = it->second;
            if (x.find(k) != x.end()) {
                int v = x[k];
                if (v <= bv) {
                    nb[k] = v;
                    b[k] -= v;
                    x.erase(k);
                    it++;
                } else {
                    x[k] = v-bv;
                    nb[k] = bv;
                    it = b.erase(it);
                }
            } else {
                it++;
            }
        }
        it = a.begin();
        while (it != a.end()) {
            int k = it->first;
            int av = it->second;
            if (x.find(k) != x.end()) {
                int v = x[k];
                if (v <= av) {
                    a[k] -= v;
                    na[k] = v;
                    x.erase(k);
                    it++;
                } else {
                    x[k] = v-av;
                    na[k] = av;
                    it = a.erase(it);
                }
            } else {
                it++;
            }
        }
        // pm("X", x);
        // pm("A", a);
        it = x.begin();
        while (it != x.end()) {
            int& v = it->second;
            auto it2 = a.begin();
            if (it2 == a.end()) break;
            while (it2 != a.end()) {
                int ka = it2->first;
                int& av = it2->second;
                if (v < av) {
                    a[ka] -= v;
                    add_map(nb, it->first, v);
                    it = x.erase(it);
                    break;
                } else if (v == av) {
                    it2 = a.erase(it2);
                    add_map(nb, it->first, v);
                    it = x.erase(it);
                    break;
                } else {
                    v -= av;
                    add_map(nb, it->first, av);
                    it2 = a.erase(it2);
                }
            }
        }
        for (auto it1 = x.begin(); it1 != x.end(); it1++) {
            add_map(nb, it1->first, it1->second);
            rs += it1->second;
        }
        a = na;
        b = nb;
    }
    // pm("A", a);
    // pm("B", b);
    // printf("RS %d\n", rs);
    return rs;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n,m;
        cin >> n >> m;
        vector<vector<int>> arr(n+3, vector<int>(m, -1));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) cin >> arr[i][j];
        }
        printf("Case #%d: %d\n", cs, solve(n,m,arr));
    }
    return 0;
}