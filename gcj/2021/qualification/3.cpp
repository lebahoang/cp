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
    int n = a.size()-1;
    for (int i = 1; i < n; i++) {
        int minV = 100000;
        int minInd = -1;
        for (int j = i; j <= n; j++) {
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

// n = 7, c = 18
// step 0: 2 4 3 x x x 1
// step 1: 1 x x x 3 4 2, c = 7
// step 2: 1 2 4 3 x x x, c = 6
// step 3: 1 2 3 4 x x x, c = 2
// step 4: 1 2 3 4 x x x, c = 1

string solve(int n, int c) {
    if (c < n-1 || c > (n*(n+1)/2-1)) {
        return " IMPOSSIBLE";
    } 
    // if (c == n-1) {
    //     string x = "";
    //     for (int i = 1; i <= n; i++) x += " " + to_string(i);
    //     return x;
    // }
    // if (c == n) {
    //     string x = " 2 1";
    //     for (int i = 3; i <= n; i++) {
    //         x += " " + to_string(i);
    //     }
    //     return x;
    // }
    vector<vector<int>> step(n+1, vector<int>(n+1, 0));
    vector<int> rs(n+1, 0);
    int left = n;
    int cost = 0;
    for (int i = 1; i < n; i++) {
        step[i][i] = i;
        cost = min(n-i+1, c-(left-2));
        step[i-1][i] = step[i][i]+cost-1;
        c -= cost;
        left--;
        for (int j = i-2; j >= 0; j--) {
            // int diff = step[j][j]-step[j+1][j];
            int diff2 = step[j+1][i] - step[j+1][j+1];
            if (step[j+1][i] <= step[j][j+1]) {
                step[j][i] = step[j][j+1]-diff2;
            } else {
                step[j][i] = step[j+1][i];
            }
        }
        // printf("i %d, cost %d\n", i, cost);
        // for (int j = 0; j <= i; j++) {
        //     vector<int> xx(n+1, 0);
        //     for (int k = 1; k <= n; k++) {
        //         xx[step[j][k]] = k;
        //     }
        //     printf("Step %d: ", j);
        //     for (int k = 1; k <= n; k++) {
        //         printf("%d ", xx[k]);
        //     }
        //     printf("\n");
        // }
    }
    for (int i = 1; i <= n; i++) {
        rs[step[0][i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (rs[i] == 0) rs[i] = n; 
    }
    
    // for (int x = 1; x <= n; x++) {
    //     printf("%d ", rs[x]);
    // }
    // printf("\n");
    // printf("Total cost %d\n", calculate(rs));
    string x = "";
    for (int i = 1; i <= n; i++) {
        x += " " + to_string(rs[i]);
    }
    return x;
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
