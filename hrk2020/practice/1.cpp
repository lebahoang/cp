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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 1.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
const int nax = 1e5 + 4;
vector<int> v[nax];

void dfs() {
}

int solve(vector<int> ts, int n) {
    
}
int main() {
    int n;
    cin >> n;
    vector<ll> ts(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> ts[i];
    }
    for (int i = 0; i < n-1; i++) {
        int a,b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    return 0;
}