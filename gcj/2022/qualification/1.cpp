#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;
const int mod = 1e9+7;
// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out

int bf(vector<int>& d, int n) {
    int rs = -1;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = i; j < n; j++) {
            if (cur+1 <= d[j]) {
                cur++;
            } else {
                break;
            }
        }
        rs = max(rs, cur);
    }
    return rs;
}
int solve(vector<int>& d, int n) {
    int rs = 0;
    for (int i = 0; i < n; i++) {
        int l = i;
        int r = n-1;
        while (l <= r) {
            int mid = (l+r)/2;
            if (mid-i+1 <= d[mid]) {
                rs = max(rs, mid-i+1);
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
    }
    return rs;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n;
        cin >> n;
        vector<int> d(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> d[i];
        }
        sort(d.begin(), d.end());
        // int rs1 = bf(d, n);
        // int rs2 = solve(d, n);
        // if (rs1 != rs2) {
        //     printf("%d, rs1 %d, rs2 %d\n", cs,rs1,rs2);
        // }
        printf("Case #%d: %d\n", cs+1, solve(d,n));
    }
    return 0;
}