#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <utility>
#include <unordered_map>

using namespace std;
using ll = long long;
int find(vector<pair<int, int>> segs, int v) {
    int l = 0;
    int r = (int)segs.size()-1;
    while (true) {
        if (l > r) break;
        int mid = (l+r)/2;
        if (segs[mid].first <= v && segs[mid].second >= v) {
            return mid;
        }
        if (segs[mid].first > v) {
            r = mid-1;
        } else if (segs[mid].second < v) {
            l = mid+1;
        }
    }
    return -1;
}
vector<vector<int>> getOneGroup(vector<vector<int>>& b) {
    unordered_map<int, vector<pair<int, int>>> m = {};
    unordered_map<int, vector<pair<int, int>>> segs = {};
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
            segs[h] = {{l, r}};
        } else {
            int mlen = (int)m[h].size();
            int llast = m[h][mlen-1].first;
            int rlast = m[h][mlen-1].second;
            if (l >= llast && l <= rlast) {
                if (r > rlast) {
                    m[h][mlen-1].second = r;
                    segs[h][(int)segs[h].size()-1].second = r;
                }
            } else {
                m[h].push_back({l, r});
                segs[h].push_back({l, r});
            }
        }
        if (rightmost < r) rightmost = r;
        // printf("%d %d %d\n", l, r, h);
    }
    sort(hs.begin(), hs.end());
    unordered_map<int, vector<pair<int, int>>> mm = {};
    int n = (int)hs.size();
    for (int i = n-1; i >= 0; i--) {
        vector<pair<int, int>> t = m[hs[i]];
        for (auto x: t) {
            int l = x.first;
            int r = x.second;
            for (int j = i-1; j >= 0; j--) {
                int ind = find(segs[hs[j]], l);
                if (ind > -1) {
                    int lj = segs[hs[j]][ind].first;
                    int rj = segs[hs[j]][ind].second;
                    
                    break;
                }
            }
        }
        
    }
    


    vector<vector<int>> rs = {};
    
    
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