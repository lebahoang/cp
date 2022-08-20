#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2104.cpp && ./s.out
using namespace std;
using ll = long long;
struct I {
    long long val;
    long long ind;
};
struct Min {
    long long cnt;
    long long val;
};
struct Max {
    long long cnt;
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
            rs[i] = Min{i-v.ind, a[i]};
        } else {
            rs[i] = Min{i+1, a[i]};
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
            rs[i] = Min{v.ind-i, a[i]};
        } else {
            rs[i] = Min{n-i, a[i]};
        }
        s.push(I{a[i], i});
    }
    return rs;
}


vector<Max> countMaxFromLeft(vector<int>& a) {
    int n = (int)a.size();
    vector<Max> rs(n);
    stack<I> s;
    s.push(I{a[0], 0});
    rs[0] = Max{1, a[0]};
    for (int i = 1; i < n; i++) {
        while (!s.empty() && s.top().val <= a[i]) {
            s.pop();
        }
        I v{-1, -1};
        if (!s.empty()) v = s.top();
        if (v.ind != -1) {
            rs[i] = Max{i-v.ind, a[i]};
        } else {
            rs[i] = Max{i+1, a[i]};
        }
        s.push(I{a[i], i});
    }
    return rs;
}
vector<Max> countMaxFromRight(vector<int>& a) {
    int n = (int)a.size();
    vector<Max> rs(n);
    stack<I> s;
    s.push(I{a[n-1], n-1});
    rs[n-1] = Max{1, a[n-1]};
    for (int i = n-2; i >= 0; i--) {
        while (!s.empty() && s.top().val < a[i]) {
            s.pop();
        }
        I v{-1, -1};
        if (!s.empty()) v = s.top();
        if (v.ind != -1) {
            rs[i] = Max{v.ind-i, a[i]};
        } else {
            rs[i] = Max{n-i, a[i]};
        }
        s.push(I{a[i], i});
    }
    return rs;
}
long long solve(vector<int>& a) {
    vector<Min> a1 = countMinFromLeft(a);
    vector<Min> a2 = countMinFromRight(a);
    vector<Max> b1 = countMaxFromLeft(a);
    vector<Max> b2 = countMaxFromRight(a);
    int n = (int)a.size();
    long long rs = 0;
    for (int i = 0; i < n; i++) {
        printf("I %d, Min Left cnt %lld, Min Right cnt %lld, Max Left cnt %lld, Max Right cnt %lld\n",
            i, a1[i].cnt, a2[i].cnt, b1[i].cnt, b2[i].cnt);
        long long minCnt = a1[i].cnt * a2[i].cnt;
        long long maxCnt = b1[i].cnt * b2[i].cnt;
        rs = rs - a[i]*minCnt + a[i]*maxCnt;
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