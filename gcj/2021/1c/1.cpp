#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <string>
#include <set>
#include <vector>
#include <utility>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out < x.txt
using namespace std;
int getI1(int a, int b) {
    int mid = (a+b)/2;
    if (mid-a < b-mid) return mid;
    else return mid-1;
}
int getI2(int a, int b) {
    int mid = (a+b)/2;
    if (mid-a > b-mid) return mid;
    else return mid+1;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n+1, 0);
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        vector<int> cnt(n+1, 0);
        cnt[0] = a[1]-1;
        for (int i = 1; i <= n; i++) {
            if (i < n) {
                if (a[i] == a[i+1] || a[i] == a[i+1]-1) continue;
                int mid = (a[i]+a[i+1])/2;
                int t1 = getI1(mid, a[i+1])-getI2(a[i], mid)+1;
                int t2 = 0;
                if (mid-1 > a[i])
                    t2 = getI1(mid-1, a[i+1])-getI2(a[i], mid-1)+1;
                int t3 = 0;
                if (mid+1 < a[i+1])
                    t3 = getI1(mid+1, a[i+1])-getI2(a[i], mid+1)+1;
                // printf("i %d, mid %d, t1 %d t2 %d t3 %d\n", i, mid, t1, t2, t3);
                cnt[i] = max({t1, t2, t3});
            } else {
                cnt[n] = k-a[n];
            }
        }
        sort(cnt.begin(), cnt.end(), [](int x, int y){
            return x > y;
        });
        // for(int i = 0; i <= n; i++) {
        //     printf("%d ", cnt[i]);
        // }
        // printf("\n");
        double rs1 = double(cnt[0]+cnt[1])/double(k);
        int v = -1;
        for (int i = 2; i <= n; i++) {
            if (a[i] == a[i-1] || a[i]-1 == a[i-1]) continue;
            int tt = a[i]-1-(a[i-1]+1)+1;
            if (v < tt) v = tt;
        }
        double rs2 = v/double(k);
        printf("Case #%d: %.9f\n", cs, max(rs1, rs2));
    }
    return 0;
}
