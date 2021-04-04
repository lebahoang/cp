#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

using namespace std;
int bs(int s, int e, vector<int>& prefix, int sv) {
    int l = s;
    int r = e;
    while (l <= r) {
        int mid = (l+r)/2;
        int v = prefix[mid]-sv;
        if ((mid == s && v >= 0) || (prefix[mid-1]-sv < 0 && v >= 0)) {
            return mid;
        } else if (prefix[mid-1]-sv >= 0) {
            r = mid-1;
        } else {
            l = mid+1;
        }
    }
    return -1;
}
int solve() {
    int rs = 0;
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m, 0));
    vector<int> start(n, -1);
    vector<vector<int>> prefix(n, vector<int>(m,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            a[i][j] -= k;
            if (a[i][j] >= 0 && start[i] == -1) {
                start[i] = j;
                rs += m-j + min(n-i-1, m-j-1);
            }
            if (j == 0) prefix[i][j] = a[i][j];
            else prefix[i][j] = prefix[i][j-1] + a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("rs %d\n", rs);
    for (int i = 0; i < n; i++) {
        printf("i %d, start[i] %d\n", i,  start[i]);
        for (int j = 0; j < start[i]; j++) {
            int ind = -1;
            if (j > 0)
                ind = bs(start[i], m-1, prefix[i], prefix[i][j-1]);
            else
                ind = bs(start[i], m-1, prefix[i], 0);
            printf("i %d, ind %d\n", i, ind);
            if (ind >= 0) {
                int x = i + (ind-j);
                if (x < n) {
                    rs += min(m-ind, n-x);
                }
            }
        }
    }
    return rs;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        printf("%d\n", solve());
    }
    return 0;
}