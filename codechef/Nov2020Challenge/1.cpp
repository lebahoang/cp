#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 1.cpp && ./s.out < x.txt
using namespace std;
const int nax = 4e6 + 5;
const int nax2 = 3e5 + 5;
bool prime[nax+5];
int ps[nax2]; 
int sieveOfEratosthenes(int n) 
{ 
    // Create a boolean array "prime[0..n]" and initialize 
    // all entries it as true. A value in prime[i] will 
    // finally be false if i is Not a prime, else true. 
    
    memset(prime, true, sizeof(prime));
    for (int p=2; p*p<=n; p++) 
    { 
        // If prime[p] is not changed, then it is a prime 
        if (prime[p] == true) 
        { 
            // Update all multiples of p 
            for (int i=p*2; i<=n; i += p) 
                prime[i] = false; 
        } 
    } 
  
    int c = 0;
    for (int p=2; p<=n; p++) {
        if (prime[p]) {
            ps[c] = p;
            c++;
        }
    } 
    return c;
}
vector<int> solve(int m) {
    int n;
    cin >> n;
    vector<int> arr(n+1, 0);
    for (int i = 0; i < n; i++) cin >> arr[i];
    map<int, vector<int>> d;
    for (int i = 0; i < n; i++) {
        auto t = d.find(arr[i]);
        if (t == d.end()) {
            d[arr[i]] = {i};
        } else {
            d[arr[i]].push_back(i);
        }
    }
    vector<int> rs(n, 0);
    int i = 0;
    for (auto t = d.begin(); t != d.end(); t++) {
        int ss = (int)t->second.size();
        int k = t->first;
        for (int j = 0; j < ss; j++) {
            // if (j < ss-1) {
            //     rs[t->second[j]] = ps[i];
            // } else {
            //     if (ss > 1) rs[t->second[j]] = ps[i]*ps[i];
            //     else rs[t->second[j]] = ps[i];
            // }
            rs[t->second[j]] = ps[i];
        }
        i++;
    }
    return rs;
}
int main() {
    int m = sieveOfEratosthenes(4000003);
    // printf("%d\n", ps[280000]);
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        vector<int> rs = solve(m);
        for (int x: rs) {
            printf("%d ", x);
        }
        printf("\n");
    }
    return 0;
}