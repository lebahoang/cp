#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <stack>
#include <queue>
    
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1556C.cpp && ./s.out < x.txt

using namespace std;

void iterate_from(int i, int n, vector<long long>& a, vector<vector<bool>>& mem) {
    stack<long long> s;
    s.push(a[i]);
    int j = i+1;
    while (j <= n) {
        if (j%2 == 1) {
            s.push(a[j]);
        } else {
            long long neg = a[j];
            while (!s.empty() && neg > 0) {
                long long x = s.top();
                s.pop();
                if (x <= neg) {
                    neg -= x;
                } else {
                    x -= neg;
                    neg = 0;
                    s.push(x);
                    break;
                }
            }
            if (s.empty() && neg == 0) {
                mem[i][j] = true;
            } else if (s.empty() && neg > 0) {
                break;
            }
        }
        j++;
    }
}
int main() {
    int t;
    cin >> t;
    for (int k = 0; k < t; k++) {
        long long rs = 0;
        int n;
        cin >> n;
        vector<long long> a(n+2, 0);
        vector<vector<bool>> mem(n+2, vector<bool>(n+2, false));
        for (int i= 1; i <= n; i++) cin >> a[i];
        for (int i= 1; i <= n; i++) {
            if (i%2 == 1) {
                iterate_from(i, n, a, mem);
                for (int j = i+1; j <= n; j++) {
                    if (j%2 == 0) {
                        if (mem[i][j])
                            printf("mem[%d][%d]: true\n", i, j);
                        else
                            printf("mem[%d][%d]: false\n", i, j);
                    }
                }
            }
        }
        for (int i = 1; i <= n; i += 2) {
            for (int j = i+1; j <= n; j += 2) {
                if (j >= i+3) {
                    if (a[i] >= a[i+1] && a[j] >= a[j-1]) {
                        long long x = min(a[i], a[i+1]);
                        long long y = min(a[j-1], a[j]);
                        long long z = min(a[i]-x, a[j]-y);
                        if (j == i+3 || mem[i+2][j-2]) {
                            rs += z+1;
                        }
                    }
                    // if (!mem[i+2][j-2] && mem[i][j]) rs++;
                } else {
                    long long x = min(a[i], a[j]);
                    rs += x;
                }
                // printf("I %d j %d RS %lld\n", i, j, rs);
            }
        }
        printf("%lld\n", rs);
    }
    return 0;
}