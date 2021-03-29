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

string solve(int n, int c) {
    if (c < n-1 || c > (n*(n+1)/2)) {
        return " IMPOSSIBLE";
    } 
    if (c == n-1) {
        string x = "";
        for (int i = 1; i <= n; i++) x += " " + to_string(i);
        return x;
    }
    if (c == n) {
        string x = " 2 1";
        for (int i = 3; i <= n; i++) {
            x += " " + to_string(i);
        }
        return x;
    }

    int nn = n;
    vector<int> rs(n+1, 0);
    rs[1] = n;
    vector<vector<int>> step(n+1, vector<int>(n+1, 0));
    step[1][1] = n;
    step[2][1] = 1;
    int place = c-n-(n-3);
    c -= n;
    for (int i = 2; i < nn; i++) {
        step[i][i] = i+place-1;
        for (int j = i-1; j >= 1; j--) {
            step[j][i] = step[j][i-1]-(step[j+1][i]-step[j+1][i-1]);
        }
        printf("step %d\n", i);
        for (int j = 1; j <= i-1; j++) {
            vector<int> t(n+1, 0);
            for (int k = 1; k <= nn; k++) {
                t[step[j][k]] = k;
            }
            for (int k = 1; k <= nn; k++) {
                printf("%d ", t[k]);
            }
            printf("\n");
        }
        printf("----------------\n");
        step[i+1][i] = i;
        n--;
        place = c-n-(n-3);
        c -= n;
    }
    for (int i = 1; i <= nn; i++) {
        rs[step[1][i]] = i;
    }
    for (int x = 1; x <= nn; x++) {
        printf("%d ", rs[x]);
    }
    printf("\n");
    printf("Total cost %d\n", calculate(rs));
    string x = "";
    for (int i = 1; i <= nn; i++) {
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
