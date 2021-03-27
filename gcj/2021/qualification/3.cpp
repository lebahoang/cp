#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <vector>
#include <utility>

// g++ -std=c++17 -O2 -o s.out 3.cpp && ./s.out < x.txt
using namespace std;
int calculate(vector<int> a) {
    int total = 0;
    int n = a.size();
    for (int i = 0; i < n-1; i++) {
        int minV = 100000;
        int minInd = -1;
        for (int j = i; j < n; j++) {
            if (a[j] < minV) {
                minV = a[j];
                minInd = j;
            }
        }
        int kk = minInd;
        for (int k = i; k <= minInd; k++) {
            if (kk < k) break;
            int x = a[k];
            a[k] = a[kk];
            a[kk] = x;
            kk--;
        }
        total += (minInd-i+1);
    }
    return total;
}
void dfs(int n, int c, int i, int total, vector<int>& x, vector<int>& ans) {
    if (i == n-1) {
        if (total == c) {
            ans = vector<int>(x.begin(), x.end());
        }
        return;
    }
    for (int k = 1; k <= n-i+1; k++) {
        x.push_back(k);
        if(total+k > c) {
            x.pop_back();
            return;
        }
        dfs(n,c,i+1,total+k,x,ans);
        x.pop_back();
        if ((int)ans.size() > 0) return;
    }
}
string solve(int n, int c) {
    vector<int> x;
    vector<int> ans;
    for (int k = 1; k <= n; k++) {
        x.push_back(k);
        dfs(n,c,1,k,x,ans);
        x.pop_back();
        if ((int)ans.size() > 0) {
            string ss = "";
            for (int x: ans) {
                ss += " " + to_string(x);
            }
            return ss;
        }
    } 
    return " IMPOSSIBLE";
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n, c;
        cin >> n >> c;
        printf("Case #%d:%s\n", cs, solve(n,c).c_str());
    }
    return 0;
}
