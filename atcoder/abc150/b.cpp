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
#include <map>
#include <set>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out b.cpp && ./s.out < x.txt

using namespace std;
void dfs(int l, int r, vector<int>& useda, vector<int>& usedb, set<pair<int, int>>& m, set<pair<int, int>, greater<pair<int, int>>>& rsList, vector<vector<pair<int, int>>>& totalList, int& rs) {
    if ((int)rsList.size() == r-l+1) {
        // sort(rsList.begin(), rsList.end());
        // for (vector<pair<int, int>> l: totalList) {
        //     for (pair<int, int> p: l) {
        //         printf("a %d b %d ", p.first, p.second);
        //     }
        //     printf("++++++++++++\n");
        // }
        // printf("------------ size of totalList %d \n", (int)totalList.size());
        vector<pair<int, int>> r = {};
        for (auto i = rsList.begin(); i != rsList.end(); i++) {
            r.push_back({i->first, i->second});
        }
        bool notAdd = false;
        for (vector<pair<int, int>> l: totalList) {
            bool f = true;
            for (int i = 0; i < (int)rsList.size(); i++) {
                if (r[i].first != l[i].first || r[i].second != l[i].second) {
                    f = false;
                    break;
                }
            }
            if (f) {
                notAdd = true;
                break;
            }
        }
        if (!notAdd) {
            totalList.push_back(r);
            rs++;
        }
        return;
    }
    for (int i = l; i <= r; i++) {
        if (useda[i] == 1) continue;
        useda[i] = 1;
        for (int j = l; j <= r; j++) {
            if (usedb[j] == 1) continue;
            pair<int, int> p = {i, j};
            if (m.find(p) == m.end()) {
                usedb[j] = 1;
                rsList.insert({i,j});
                dfs(l, r, useda, usedb, m, rsList, totalList, rs);
                rsList.erase({i, j});
                usedb[j] = 0;
            }
        }
        useda[i] = 0;
    }
}
long long solve(vector<vector<int>>& list, int n, int k) {
    vector<int> useda(n+5, 0);
    vector<int> usedb(n+5, 0);
    vector<vector<int>> cal(n+1, vector<int>(5, 0));
    set<pair<int, int>> m = {};
    for (vector<int> p: list) {
        m.insert({p[0], p[1]});
    }
    int rs = 0;
    set<pair<int, int>, greater<pair<int, int>>> rsList;
    vector<vector<pair<int, int>>> totalList = {};
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            if (i+j > n) continue;
            dfs(i, i+j, useda, usedb, m, rsList, totalList, rs);
            // for (int k = 1; k <= n; k++) printf("%d ", useda[k]);
            // printf("\n");
            // for (int k = 1; k <= n; k++) printf("%d ", usedb[k]);
            // printf("\n");
            cal[i][j] = rs;
            // printf("i %d, length %d, ways %d\n", i, j+1, cal[i][j]);
            rs = 0;
            rsList.clear();
            totalList = {};
        }
    }
    return 0l;
}
int main() {
    vector<vector<int>> list = {
        {1,2}, {1,3}
    };
    int n = 2000;
    int k = 4;
    printf("%lld\n", solve(list, n, k));
    return 0;
}