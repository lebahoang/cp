#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out
using namespace std;
struct X {
    int i;
    int s;
};
int solve(vector<int>& scores, vector<vector<int>>& edges) {
    int n = (int)scores.size();
    int m = (int)edges.size();
    vector<vector<X>> nei(n, vector<X>{});
    for (int i = 0; i < m; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        nei[a].push_back(X{b, scores[b]});
        nei[b].push_back(X{a, scores[a]});
    }
    for (int i = 0; i < n; i++) {
        sort(nei[i].begin(), nei[i].end(), [](X i, X j){
            return i.s < j.s;
        });
    }
    int rs = -1;
    for (int i = 0; i < n; i++) {
        int lenI = (int)nei[i].size();
        if (lenI < 2) continue;
        for (X& j: nei[i]) {
            int total = scores[i] + scores[j.i];
            int lenJ = (int)nei[j.i].size();
            int third = -1;
            if (lenJ < 2) continue;
            if (j.i != nei[i][lenI-1].i) {
                third = nei[i][lenI-1].i;
                total += nei[i][lenI-1].s;
            } else {
                third = nei[i][lenI-2].i;
                total += nei[i][lenI-2].s;
            }
            if (i != nei[j.i][lenJ-1].i) {
                if (third != nei[j.i][lenJ-1].i) total += nei[j.i][lenJ-1].s;
                else if (i != nei[j.i][lenJ-2].i ) total += nei[j.i][lenJ-2].s;
                else if (lenJ >= 3) total += nei[j.i][lenJ-3].s;
                else total = -1000;
            } else {
                if (third !=  nei[j.i][lenJ-2].i) total += nei[j.i][lenJ-2].s;
                else total = -1000;
            }
            printf("I %d J %d total %d\n", i, j.i, total);
            rs = max(rs, total);
        }
    }
    return rs;
}
int main() {
    vector<int> scores = {5,2,9,8,4};
    vector<vector<int>> edges = {
        {0,1},
        {1,2},
        {2,3},
        {0,2},
        {1,3},
        {2,4}
    };
    printf("%d\n", solve(scores, edges));
    return 0;
}