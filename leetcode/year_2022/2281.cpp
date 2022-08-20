#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2281.cpp && ./s.out
using namespace std;
using ll = long long;
struct I {
    long long val;
    long long ind;
};
struct Min {
    long long ind;
    long long val;
};
vector<Min> countMinFromLeft(vector<int>& a) {
    int n = (int)a.size();
    vector<Min> rs(n);
    stack<I> s;
    s.push(I{a[0], 0});
    rs[0] = Min{1, a[0]};
    for (int i = 1; i < n; i++) {
        while (!s.empty() && s.top().val >= a[i]) {
            s.pop();
        }
        I v{-1, -1};
        if (!s.empty()) v = s.top();
        if (v.ind != -1) {
            rs[i] = Min{v.ind+1, a[i]};
        } else {
            rs[i] = Min{0, a[i]};
        }
        s.push(I{a[i], i});
    }
    return rs;
}
vector<Min> countMinFromRight(vector<int>& a) {
    int n = (int)a.size();
    vector<Min> rs(n);
    stack<I> s;
    s.push(I{a[n-1], n-1});
    rs[n-1] = Min{1, a[n-1]};
    for (int i = n-2; i >= 0; i--) {
        while (!s.empty() && s.top().val > a[i]) {
            s.pop();
        }
        I v{-1, -1};
        if (!s.empty()) v = s.top();
        if (v.ind != -1) {
            rs[i] = Min{v.ind-1, a[i]};
        } else {
            rs[i] = Min{n-1, a[i]};
        }
        s.push(I{a[i], i});
    }
    return rs;
}

long long solve(vector<int>& a) {
    vector<Min> a1 = countMinFromLeft(a);
    vector<Min> a2 = countMinFromRight(a);
    long long mod = 1e9 + 7;
    int n = (int)a.size();
    long long rs = 0;
    for (int i = 0; i < n; i++) {
        printf("I %d, Min Left IND %lld, Min Right IND %lld\n",
            i, a1[i].ind, a2[i].ind);
        
    }
    return rs;
}

int main() {
    // vector<int> a = {13, 2, 47, 15, 46, 36, 23, 24, 28, 44, 48, 19, 35};
    vector<int> a = {5,3,330,2,1};
    // vector<int> a = {1,3,3};
    printf("%lld\n", solve(a));
    return 0;
}