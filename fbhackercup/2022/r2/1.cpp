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
using ll = long long;
const ll mod = 1e9+7;

// For test speed: g++ -std=c++17 -Wall -lm -O2 -o s.out 1.cpp && time ./s.out < x.txt
// g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined -o s.out 1.cpp && ./s.out < x.txt
void pp(vector<int>& x) {
    for (int i: x) {
        printf("%d ", i);
    }
    printf("\n");
}
vector<int> diff(vector<int>& x, vector<int>& y) {
    int n = (int)x.size();
    vector<int> rs(n, 0);
    for (int i = 0; i < n; i++) {
        rs[i] = y[i]-x[i];
    }
    return rs;
}
vector<vector<int>> compute(string& s) {
    int n = (int)s.length();
    vector<vector<int>> a(n, vector<int>(28, 0));
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            vector<int> t(28, 0);
            t[s[i] - 'a']++;
            a[i] = t;
        } else {
            vector<int> t(a[i-1].begin(), a[i-1].end());
            t[s[i] - 'a']++;
            a[i] = t;
        }
    }
    return a;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        string str;
        cin >> str;
        // printf("Size s: %lu\n", str.length());
        vector<vector<int>> a = compute(str);
        int q;
        cin >> q;
        int rs = 0;
        for (int i = 0; i < q; i++) {
            int s, e;
            cin >> s >> e;
            s--;
            e--;
            if ((e-s+1)%2 == 0) continue;
            else if (e-s+1 == 1) {
                rs++;
                continue;
            }
            int mid = (s+e)/2;
            vector<int> x;
            if (s-1 >= 0) x = diff(a[s-1], a[mid]);
            else x = a[mid];
            vector<int> y = diff(a[mid], a[e]);
            int cnt = 0;
            for (int j = 0; j < 28; j++) {
                cnt += abs(y[j] - x[j]);
            }
            // pp(x);
            // pp(y);
            // printf("Count %d\n", cnt);
            if (cnt == 1) rs++;
            else {
                if (s-1 >= 0) x = diff(a[s-1], a[mid-1]);
                else x = a[mid-1];
                y = diff(a[mid-1], a[e]);
                cnt = 0;
                for (int j = 0; j < 28; j++) {
                    cnt += abs(y[j] - x[j]);
                }
                if (cnt == 1) rs++;
            }
        }
        printf("Case #%d: %d\n", cs, rs);
    }
    return 0;
}