#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

pair<int, int> solve(int n, vector<string>& m) {
    vector<vector<pair<int, int>>> t = {};
    int x1 = 1e9;
    for (int i = 0; i < n; i++) {
        bool ok = true;
        int c = 0;
        vector<pair<int, int>> l = {};
        for (int j = 0; j < n; j++) {
            if (m[i][j] == '.') {
                c++;
                l.push_back({i,j});
            }
            else if (m[i][j] == 'O') {
                ok = false;
                break;
            }
        }
        if (ok) {
            if (c == x1) {
               t.push_back(l);
            } else if (c < x1) {
                x1 = c;
                t = {l};
            }
        }
    }

    for (int j = 0; j < n; j++) {
        bool ok = true;
        int c = 0;
        vector<pair<int, int>> l = {};
        for (int i = 0; i < n; i++) {
            if (m[i][j] == '.') {
                c++;
                l.push_back({i,j});
            }
            else if (m[i][j] == 'O') {
                ok = false;
                break;
            }
        }
        if (ok) {
            if (c == x1) {
               t.push_back(l);
            } else if (c < x1) {
                x1 = c;
                t = {l};
            }
        }
    }
    int cnt = 0;
    if (x1 == 1) {
        cnt = 1;
        sort(t.begin(), t.end(), [](vector<pair<int, int>>& a, vector<pair<int, int>>& b){
            if (a[0].first < b[0].first) return true;
            if (a[0].first > b[0].first) return false;
            return a[0].second < b[0].second;
        });
        for (int i = 1; i < (int)t.size(); i++) {
            if (t[i][0].first != t[i-1][0].first || t[i][0].second != t[i-1][0].second) cnt++;
        }
    } else {
        cnt = (int)t.size();
    }
    if (x1 == 1e9) return {-1, -1};
    return {x1, cnt};
}

int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        int n;
        cin >> n;
        vector<string> m(n, "");
        for (int i = 0; i < n; i++) cin >> m[i];
        pair<int, int> rs = solve(n, m);
        if (rs.first == -1) {
            printf("Case #%d: Impossible\n", c+1);
        } else {
            printf("Case #%d: %d %d\n", c+1, rs.first, rs.second);
        }
        
    }
    return 0;
}