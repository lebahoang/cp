#include <random>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 329.cpp && ./s.out
using namespace std;
using ll = long long;
vector<vector<int>> generate_g() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(0,2147483647);
    int n = 200;
    int m = 200;
    vector<vector<int>> g(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[i][j] = dist(rng);
        }
    }
    return g;
}
int dfs(int i, int j, int n, int m,
    vector<vector<int>>& g, vector<vector<bool>>& v, vector<vector<int>>& c, vector<vector<int>>& dp) {
    
    if (dp[i][j] > -1) return dp[i][j];
    int maxV = 1;
    for (vector<int>& x: c) {
        int a = i+x[0];
        int b = j+x[1];
        if (a >= 0 && a < n && b >= 0 && b < m && !v[a][b] && g[a][b] > g[i][j]) {
            v[a][b] = true;
            maxV = max(maxV, dfs(a,b,n,m,g,v,c,dp)+1);
            v[a][b] = false;
        }
    }
    dp[i][j] = maxV;
    return maxV;
}
int solve(vector<vector<int>>& g) {
    int n = (int)g.size();
    int m = (int)g[0].size();
    vector<vector<bool>> v(n, vector<bool>(m, false));
    vector<vector<int>> c = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    vector<vector<int>> dp(n+2, vector<int>(m+2, -1));
    int rs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            v[i][j] = true;
            rs = max(rs, dfs(i,j,n,m,g,v,c,dp));
            v[i][j] = false;
            // printf("dp[%d][%d] %d\n", i, j, dp[i][j]);
        }
    }
    return rs;
}
int main() {
    // vector<vector<int>> g = {
    //     {9,9,4},
    //     {6,6,8},
    //     {2,1,1}
    // };
    // vector<vector<int>> g = {
    //     {3,4,5},
    //     {3,2,6},
    //     {2,2,1}
    // };
    vector<vector<int>> g = {
        {1}
    };
    printf("%d\n", solve(g));
    return 0;
}