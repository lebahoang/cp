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
    if (c < n-1 || c > (n*(n+1)/2)) {
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


    
    for (int i = 1; i <= n; i++) {
        rs[step[1][i]] = i;
    }
    for (int x = 1; x <= n; x++) {
        printf("%d ", rs[x]);
    }
    printf("\n");
    printf("Total cost %d\n", calculate(rs));
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
