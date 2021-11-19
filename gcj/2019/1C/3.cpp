#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <vector>
#include <utility>

// g++ -std=c++17 -O2 -o s.out 1.cpp && ./s.out < x.txt
using namespace std;
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n;
        cin >> n;
        vector<int> a(n, 0);
        int total = 0;
        for (int i = 0; i < n; i++) cin >> a[i];
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
            printf("i %d, cost %d\n", i, minInd-i+1);
            total += (minInd-i+1);
        }
        printf("Case #%d: %d\n", cs, total);
    }
    return 0;
}
