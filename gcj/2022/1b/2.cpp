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

// For test speed: g++ -std=c++17 -Wall -lm -O2 -o s.out 2.cpp && time ./s.out < x.txt
// g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined -o s.out 2.cpp && ./s.out < x.txt

int find(ll k, vector<ll>& u) {
    int n = (int)u.size();
    if (u[0] >= k) return -1;
    else if (u[n-1] < k) return n-1;
    int l = 0;
    int r = n-1;
    while (l < r) {
        int mid = (l+r)/2;
        if (u[mid] < k && u[mid+1] >= k) return mid;
        else if (u[mid] >= k) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return -1000;
}

ll goLeft(vector<ll>& u, int ind, int j, ll k,  vector<ll>& prefix,  vector<ll>& suffix, int& stopPosition) {
    if (ind < j) {
        if (ind == -1) {
            stopPosition = -1;
            return 0;
        }
        stopPosition = 0;
        return k-u[ind] + prefix[ind];
    } else if (ind > j) {
        if (j == 0) {
            stopPosition = 1;
            return k-u[ind] + prefix[ind]-prefix[1];
        }
        stopPosition = 0;
        return k-u[ind] + prefix[ind];
    } else {
        if (ind-1 < 0) {
            stopPosition = -1;
            return 0;
        }
        stopPosition = 0;
        return k-u[ind-1] + prefix[ind-1];
    }
}

ll goFromStart(vector<ll>& u, int stopPosition, ll k) {
    if (stopPosition < 0) {
        return 0;
    } else {
        return k-u[stopPosition];
    } 
}
ll goRightFromLeft(vector<ll>& u, int ind, int j, int k,  vector<ll>& prefix,  vector<ll>& suffix) {
    int n = (int)u.size();
    if (ind < j) {
        if (j == ind+1) {
            if (ind+2 >= n) {
                return 0 + u[j] - k;
            }
            return u[ind+2]-k + suffix[ind+2] + u[n-1] - u[j];
        } else if (j == n-1) {
            return u[ind+1]-k + suffix[ind+1];
        } else {
            return u[ind+1]-k + suffix[ind+1] + u[n-1] - u[j];
        }
    } else {
        if (ind+1 >= n) {
            return 0 + k - u[j];
        }
        return u[ind+1]-k + suffix[ind+1] + u[n-1] - u[j];
    }
}
ll goRight(vector<ll>& u, int ind, int j, ll k,  vector<ll>& prefix,  vector<ll>& suffix, int& stopPosition) {
    int n = (int)u.size();
    if (ind < j) {
        if (j == ind+1) {
            if (ind+2 >= n) {
                stopPosition = -1;
                return 0;
            }
            stopPosition = n-1;
            return u[ind+2]-k + suffix[ind+2];
        } else if (j == n-1) {
            stopPosition = n-2;
            return u[ind+1]-k + suffix[ind+1]-suffix[n-2];
        } else {
            stopPosition = n-1;
            return u[ind+1]-k + suffix[ind+1];
        }
    } else {
        if (ind+1 >= n) {
            stopPosition = -1;
            return 0;
        }
        stopPosition = n-1;
        return u[ind+1]-k + suffix[ind+1];
    }
}
ll goFromEnd(vector<ll>& u, int stopPosition, ll k) {
    if (stopPosition < 0) {
        return 0;
    } else {
        return u[stopPosition] - k;
    }
}
ll goLeftFromRight(vector<ll>& u, int ind, int j, ll k,  vector<ll>& prefix,  vector<ll>& suffix) {
    if (ind < j) {
        if (ind == -1) {
            return 0 + u[j] - k;
        }
        return k-u[ind] + prefix[ind] + u[j]-u[0];
    } else if (ind > j) {
        if (j == 0) {
            return k-u[ind] + prefix[ind]-prefix[1] + u[1]-u[j];
        }
        return k-u[ind] + prefix[ind] + u[j] - u[0];
    } else {
        if (ind-1 < 0) {
            return 0 + k-u[j];
        }
        return k-u[ind-1] + prefix[ind-1] + u[j]-u[0];
    }
}

int main() {
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        int n, p;
        cin >> n >> p;
        vector<vector<ll>> u(n, vector<ll>(p, 0));
        vector<vector<ll>> prefix(n, vector<ll>(p, 0));
        vector<vector<ll>> suffix(n, vector<ll>(p, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                cin >> u[i][j];
            }
            sort(u[i].begin(), u[i].end());
            // for (int j = 0; j < p; j++) {
            //     if (j == 0) prefix[i][j] = 0;
            //     else prefix[i][j] = prefix[i][j-1] + u[i][j] - u[i][j-1];
            // }
            // for (int j = p-1; j >= 0; j--) {
            //     if (j == p-1) suffix[i][j] = 0;
            //     else suffix[i][j] = suffix[i][j+1] + u[i][j+1] - u[i][j];
            // }
            for (int j = 0; j < p; j++) {
                if (j == 0) {
                    prefix[i][j] = 0;
                    suffix[i][p-1-j] = 0;
                } else {
                    prefix[i][j] = prefix[i][j-1] + u[i][j] - u[i][j-1];
                    suffix[i][p-1-j] = suffix[i][p-1-j+1] + u[i][p-1-j+1] - u[i][p-1-j];
                }
            }
        }
        ll rs = 1e16;
        // vector<vector<ll>> dp(n, vector<ll>(p, 1e16));
        vector<ll> dp0(p, 1e16);
        vector<ll> dp1(p, 1e16);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < p; k++) {
                    int valK = 0;
                    ll prevDP = 0;
                    if (i >= 1) {
                        valK = u[i-1][k];
                        // prevDP = dp[i-1][k];
                        prevDP = dp0[k];
                    }
                    int ind = find(valK, u[i]);
                    // printf("I %d J %d, K %d, valK %d, ind %d\n", i, j, k, valK, ind);
                    int stopPosition1 = -1;
                    ll costGoLeft = goLeft(u[i], ind, j, valK, prefix[i], suffix[i], stopPosition1);
                    ll costGoFromStart = goFromStart(u[i], stopPosition1, valK);
                    ll costGoRightFromLeft = goRightFromLeft(u[i], ind, j, valK, prefix[i], suffix[i]);
                    ll cost1 = costGoLeft + costGoFromStart + costGoRightFromLeft;
                    // printf("costGoLeft %lld, costGoFromStart %lld, costGoRightFromLeft %lld, Cost1 %lld\n", costGoLeft, costGoFromStart, costGoRightFromLeft, cost1);
                    int stopPosition2 = -1;
                    ll costGoRight = goRight(u[i], ind, j, valK, prefix[i], suffix[i], stopPosition2);
                    ll costGoFromEnd = goFromEnd(u[i], stopPosition2, valK);
                    ll costGoLeftFromRight = goLeftFromRight(u[i], ind, j, valK, prefix[i], suffix[i]);
                    ll cost2 = costGoRight + costGoFromEnd + costGoLeftFromRight;
                    // printf("costGoRight %lld, costGoFromEnd %lld, costGoLeftFromRight %lld, Cost2 %lld\n", costGoRight, costGoFromEnd, costGoLeftFromRight, cost2);
                    // dp[i][j] = min(dp[i][j], prevDP + min(cost1, cost2));
                    dp1[j] = min(dp1[j], prevDP + min(cost1, cost2));
                }
                if (i == n-1) {
                    // rs = min(rs, dp[i][j]);
                    rs = min(rs, dp1[j]);
                }
            }
            // for (int j = 0; j < p; j++) {
            //     dp0[j] = dp1[j];
            //     dp1[j] = 1e16;
            // }
            dp0 = vector<ll>(dp1.begin(), dp1.end());
            fill(dp1.begin(), dp1.end(), 1e16);
        }
        
        printf("Case #%d: %lld\n", cs, rs);
    }
    return 0;
}