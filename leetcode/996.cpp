#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>

using namespace std;
bool is_square(int num) {
    if (num == 0) return true;
    int k = sqrt(num);
    bool f = false;
    for (int x = 1; x <= k+1; x++) {
        if (x*x == num) {
            f = true;
            break;
        }
    }
    return f;
}
void fill(vector<vector<int>>& table, vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i < n; i++) {
        bool f = is_square(a[i]);
        if (f) table[i][n] = 1;
        for (int j = i+1; j < n; j++) {
            f = is_square(a[i]+a[j]);
            if (f) {
                table[i][j] = 1;
                table[j][i] = 1;
            }
        }
    }
}

int solve(vector<int>& a) {
    int n = (int)a.size();
    vector<vector<int>> table(n+1, vector<int>(n+1, 0));
    fill(table, a);
    vector<vector<int>> dp(n, vector<int>(1 << n, 0));
    set<int> s;
    for (int i = 1; i < (1 << n); i++) {
        s.clear();
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                if (s.find(a[j]) != s.end()) continue;
                s.insert(a[j]);
                int ii = i & (~(1 << j));
                if (ii == 0) {
                    if (table[j][n] == 1) {
                        dp[j][i] = 1;
                    }
                } else {
                    for (int k = 0; k < n; k++) {
                        if ((ii & (1 << k)) != 0 && table[j][k] == 1) {
                            if (dp[k][ii] == 0 && ii == (1 << k))
                                dp[j][i] += 1;
                            else
                                dp[j][i] += dp[k][ii];
                        }
                    }
                }
                
            }
            // printf("dp[%d][%d] %d\n", j, i, dp[j][i]);
        }
        
    }
    s.clear();
    int rs = 0;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        if (s.find(x) == s.end()) {
            s.insert(x);
            rs += dp[i][(1 << n)-1];
        }
    }
    return rs;
}
int main() {
    vector<int> a = {1,8,17,8,17,8};
    printf("%d\n", solve(a));
    return 0;
}