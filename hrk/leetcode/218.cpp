#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <unordered_map>

using namespace std;
using ll = long long;
vector<vector<int>> getOneGroup(vector<vector<int>>& b) {
    unordered_map<int, vector<int>> m = {};
    unordered_map<int, vector<int>> mm = {};
    vector<int> hs = {};
    int rightmost = -1;
    for (int i = 0; i < (int)b.size(); i++) {
        int l = b[i][0];
        int r = b[i][1];
        int h = b[i][2];
        auto temp = m.find(h);
        if (temp == m.end()) {
            hs.push_back(h);
            m[h] = {{l, r}};
            mm[h] = {{l, r}};
        } else {
            if (m[h][0] > l) {
                m[h][0] = l;
                mm[h][0] = l;
            }
            if (m[h][1] < r) {
                m[h][1] = r;
                mm[h][1] = r;
            }
        }
        if (rightmost < r) rightmost = r;
        // printf("%d %d %d\n", l, r, h);
    }
    sort(hs.begin(), hs.end());
    int n = (int)hs.size();
    for (int i = n-1; i >= 0; i--) {
        int l = m[hs[i]][0];
        int r = m[hs[i]][1];
        for (int j = i-1; j >= 0; j--) {
            int a = m[hs[j]][0];
            int b = m[hs[j]][1];
            if (r > a && r < b) {
                if (a >= l) {
                    mm[hs[j]][0] = r;
                } else {
                    // printf("dadasdsa %d\n", hs[j]);
                    mm[hs[j]].insert(mm[hs[j]].end()-1, r);
                    // for (auto x: mm[hs[j]]) {
                    //     printf("ddddd %d\n", x);
                    // }
                }
                break;
            }
        }
    }


    vector<vector<int>> rs = {};
    for (auto t: mm) {
        for (int i = 0; i < (int)t.second.size()-1; i++) {
            rs.push_back({t.second[i], t.first});
        }  
    }
    
    rs.push_back({rightmost, 0});
    return rs;
}

vector<vector<int>> solve(vector<vector<int>>& b) {
    vector<vector<int>> ans = {};
    sort(b.begin(), b.end());
    vector<vector<int>> g = {};
    int gl = b[0][0];
    int gr = b[0][1];
    for (auto it: b) {
        int l = it[0];
        int r = it[1];
        int h = it[2];
        if (l >= gl && l <= gr) {
            g.push_back({l,r,h});
            if (r > gr) gr = r;
        } else {
            auto rs = getOneGroup(g);
            for (auto t: rs) {
                ans.push_back({t[0], t[1]});
            }
            // printf("------- \n");
            g.clear();
            g.push_back({l,r,h});
            gl = l;
            gr = r;
        }
    }
    if (!g.empty()) {
        auto rs = getOneGroup(g);
        for (auto t: rs) {
            ans.push_back({t[0], t[1]});
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}
int main() {
    // vector<vector<int>> b = {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    // vector<vector<int>> b = {{2,10,5}, {4,6,100}, {7,8,106}};
    vector<vector<int>> b = {{1,2,1}, {1,2,2}, {1,2,3}};
    auto rs = solve(b);
    printf("++++++++\n");
    for (auto x: rs) printf("%d %d\n", x[0], x[1]);
    return 0;
}