#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <stack>
#include <queue>

using namespace std;
void pv(vector<pair<int, int>> v) {
    for (auto x: v) {
        printf("%d %d;", x.first, x.second);
    }
    printf("\n");
}

int solve(int n, vector<int>& in_v, vector<vector<int>>& out_v) {
    vector<int> round_v(n+2, -1);
    vector<pair<int, int>> l = {};
    queue<pair<int, int>> s = {};
    vector<int> ss = {};
    for (int i = 1; i <= n; i++) {
        if (in_v[i] == 0) {
            round_v[i] = 1;
            // ss.push_back(i);
            s.push({i, round_v[i]});
        }
    }
    // sort(ss.begin(), ss.end());
    // for (int i: ss) s.push({i, round_v[i]});
    int rs = -1;
    while (!s.empty()) {
        pair<int, int> it = s.front();
        s.pop();
        l.push_back(it);
        for (int& j: out_v[it.first]) {
            in_v[j]--;
            int round = 0;
            if (j < it.first) {
                round = it.second+1;
            } else {
                round = it.second;
            }
            round_v[j] = max(round_v[j], round);
            if (in_v[j] == 0) {
                s.push({j, round_v[j]});
            }
        }
    }
    int m = (int)l.size();
    if (m < n) return -1;
    // pv(l);
    for (int i = 1; i <= n; i++) {
        rs = max(rs, round_v[i]);
    }
    return rs;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n;
        cin >> n;
        vector<int> in_v(n+2, 0);
        vector<vector<int>> out_v(n+2, vector<int>{});
        for (int i = 1; i <= n; i++) {
            int k;
            cin >> k;
            int in;
            for (int j = 0; j < k; j++) {
                cin >> in;
                in_v[i]++;
                out_v[in].push_back(i);
            }
        }
        // for (int i = 1; i <= n; i++) {
        //     vector<int> a = {};
        //     vector<int> b = {};
        //     for (int j: out_v[i]) {
        //         if (j > i) a.push_back(j);
        //         else b.push_back(j);
        //     }
        //     sort(a.begin(), a.end());
        //     sort(b.begin(), b.end());
        //     a.insert(a.end(), b.begin(), b.end());
        //     out_v[i] = a;
        // }
        printf("%d\n", solve(n, in_v, out_v));
    }
    return 0;
}