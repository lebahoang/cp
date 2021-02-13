#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;
using ll = long long;
const int mod = 1e9+7;
const int NMAX = 4e5 + 2;

bool primes[50];
int dpprev[400];
int dp[400];
vector<int> nums[400];
// int tdp[NMAX][500];
int total[NMAX];

bool isAccepted(vector<int> a, int n) {
    for (int i = 0; i <= n-3; i++) {
        int x = 0;
        for (int j = 0; j < 3; j++) {
            x += a[i+j];
        }
        if (!primes[x]) return false;
    }
    for (int i = 0; i <= n-4; i++) {
        int x = 0;
        for (int j = 0; j < 4; j++) {
            x += a[i+j];
        }
        if (!primes[x]) return false;
        
    }
    for (int i = 0; i <= n-5; i++) {
        int x = 0;
        for (int j = 0; j < 5; j++) {
            x += a[i+j];
        }
        if (!primes[x]) return false;  
    }
    return true;
}

void solve() {
    vector<int> pref = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    for (int i = 0; i < pref.size(); i++) {
        primes[pref[i]] = true;
    }
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;
    vector<int> e;
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (i > 0) total[1]++;
        for (int j = 0; j < 10; j++) {
            if (i > 0) total[2]++;
            for (int k = 0; k < 10; k++) {
                if (i > 0 && primes[i+j+k]) total[3]++;
                for (int m = 0; m < 10; m++) {
                    if (i > 0 && primes[i+j+k] && primes[j+k+m] && primes[i+j+k+m]) total[4]++;
                    for (int p = 0; p < 10; p++) {
                        if (isAccepted({i,j,k,m,p}, 5)) {
                            count++;
                            a.push_back(p);
                            b.push_back(m+p);
                            c.push_back(k+m+p);
                            d.push_back(k+m+p+j);
                            e.push_back(k+m+p+j+i);
                            if (i > 0) {
                                dpprev[a.size()-1]++;
                                total[5]++;
                            }
                        }
                    }
                }
            }
        }
    }
    // printf("%d\n", count);

    for(int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            if (i == j) continue;
            int f = a[i];
            if (b[i]-a[j] == f && c[i]-b[j] == f && d[i]-c[j] == f && e[i]-d[j] == f) {
                nums[i].push_back(j);
            }
        }
        // printf("%lu\n", nums[i].size());
    }

    int n = NMAX-1;
    for (int i = 6; i <= n; i++) {
        for (int k = 0; k < a.size(); k++) {
            for (int x = 0; x < nums[k].size(); x++) {
                dp[k] = (dp[k]%mod + dpprev[nums[k][x]]%mod)%mod;
            }
            
        }
        for (int k = 0; k < a.size(); k++) {
            total[i] = (total[i]%mod + dp[k]%mod)%mod;
            dpprev[k] = dp[k];
            dp[k] = 0;
        }
    }
}

int main() {
    solve();
    int q, n;
    cin >> q;
    for (int x = 1; x <= q; x++) {
        cin >> n;
        printf("%d\n", total[n]);
    }
    return 0;
}
