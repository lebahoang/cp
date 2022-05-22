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
const int mod = 1e9+7;

// For test speed: g++ -std=c++17 -Wall -lm -O2 -o s.out 41D.cpp && time ./s.out < x.txt
// g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined -o s.out 41D.cpp && ./s.out < x.txt
struct I {
    int j;
    int z;
    string c;
};

int main() {
    int n,m,k;
    cin >> n >> m >> k;
    
    vector<vector<int>> x(n, vector<int>(m, -1));
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k+2, -1)));
    vector<vector<vector<I>>> path(n, vector<vector<I>>(m, vector<I>(k+2, I{-1,-1,""})));
    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        for (int j = 0; j < m; j++) {
            x[i][j] = t[j]-'0';
        }
    }
    for (int j = 0; j < m; j++) {
        int z = x[n-1][j]%(k+1);
        dp[n-1][j][z] = x[n-1][j];
        path[n-1][j][z] = I{-1, -1,""};
    }
    for (int i = n-2; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            for (int z = 0; z <= k; z++) {
                int zz = (z + (x[i][j]%(k+1)))%(k+1);
                if (j-1 >= 0) {
                    if (dp[i+1][j-1][z] >= 0 && dp[i+1][j-1][z] + x[i][j] > dp[i][j][zz]) {
                        dp[i][j][zz] = dp[i+1][j-1][z] + x[i][j];
                        path[i][j][zz] = I{j-1, z, "R"};
                    }
                        
                }
                if (j+1 < m) {
                    if (dp[i+1][j+1][z] >= 0 && dp[i+1][j+1][z] + x[i][j] > dp[i][j][zz]) {
                        dp[i][j][zz] = dp[i+1][j+1][z] + x[i][j];
                        path[i][j][zz] = I{j+1, z, "L"};
                    }   
                }
                // printf("dp[%d][%d][%d]: %d;  path: %d %d %s\n", i,j,zz,dp[i][j][zz], path[i][j][zz].j, path[i][j][zz].z, path[i][j][zz].c.c_str());
            }
        }
    }
    int rs = -1;
    int rsJ = -1;
    int rsZ = 0;
    string rsP = "";
    for (int j = 0; j < m; j++) {
        if (dp[0][j][0] > rs) {
            rs = dp[0][j][0];
            rsJ = j;
        }
    }
    if (rs == -1) {
        printf("%d\n", rs);
        return 0;
    }
    int i = 0;
    while (true) {
        if (path[i][rsJ][rsZ].j == -1) break;
        // printf("%d %d %d;;; %d %d\n", i, rsJ, rsZ, path[i][rsJ][rsZ].j, path[i][rsJ][rsZ].z);
        string c = path[i][rsJ][rsZ].c;
        rsP.append(c);
        int tJ = path[i][rsJ][rsZ].j;
        int tZ = path[i][rsJ][rsZ].z;
        i++;
        rsJ = tJ;
        rsZ = tZ;
    }
    reverse(rsP.begin(), rsP.end());
    printf("%d\n", rs);
    printf("%d\n", rsJ+1);
    printf("%s\n", rsP.c_str());
    return 0;
}
