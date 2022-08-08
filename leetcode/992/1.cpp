#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out
using namespace std;
struct X {
    int cnt;
    queue<int> sinds;
    int s;
    int e;
};
int computeSum(int n) {
    return (n*(1+n))/2;
}
int increaseSubArray(vector<int>& arr, int k, int i, unordered_map<int, X>& m) {
    int l = (int)arr.size();
    for (int x = i; x < l; x++) {
        auto it = m.find(arr[x]);
        if (it == m.end()) {
            int msz = (int)m.size();
            if (msz + 1 > k) {
                return x-1;
            }
            queue<int> q;
            q.push(x);
            m[arr[x]] = X{1, q, x, x};
        } else {
            m[arr[x]].cnt++;
            m[arr[x]].sinds.push(x);
            m[arr[x]].e = x;
        }
    }
    if ((int)m.size() == k) {
        return l-1;
    }
    return l;
}
int decreaseSubArray(vector<int>& arr, int k, int i, unordered_map<int, X>& m) {
    int l = (int)arr.size();
    for (int x = i; x < l; x++) {
        auto it = m.find(arr[x]);
        assert(it != m.end());
        if (it->second.cnt == 1) {
            m.erase(it->first);
            return x+1;
        } else {
            m[arr[x]].cnt--;
            m[arr[x]].sinds.pop();
            m[arr[x]].s = m[arr[x]].sinds.front();
        }
    }
    return l;
}
unordered_map<int,int> getSubtractOfElement(vector<int>& arr) {
    unordered_map<int, int> m;
    int l = (int)arr.size();
    int cur = -1;
    int cnt = 0;
    for (int i = 0; i < l; i++) {
        if (cur == -1 || cur != arr[i]) {
            if (cnt > 1) {
                if (m.find(cur) == m.end()) {
                    m[cur] = computeSum(cnt-1);
                } else {
                    m[cur] += computeSum(cnt-1);
                }
            }
            cnt = 1;
            cur = arr[i];
        } else {
            cnt++;
        }
    }
    if (cnt > 1) {
        if (m.find(cur) == m.end()) {
            m[cur] = computeSum(cnt-1);
        } else {
            m[cur] += computeSum(cnt-1);
        }
    }
    return m;
}
int solve(vector<int>& arr, int k) {
    int rs = 0;
    int l = (int)arr.size();
    if (k == 1) {
        rs = l;
        int cur = -1;
        int cnt = 0;
        for (int i = 0; i < l; i++) {
            if (cur == -1 || cur != arr[i]) {
                if (cnt > 1) {
                    rs += computeSum(cnt-1);
                }
                cnt = 1;
                cur = arr[i];
            } else {
                cnt++;
            }
        }
        if (cnt > 1) {
            rs += computeSum(cnt-1);
        }
        return rs;
    }
    int i = 0;
    int j = -1;
    unordered_map<int, X> m;
    unordered_map<int, int> subOfElement = getSubtractOfElement(arr);
    while (j < l) {
        j = increaseSubArray(arr, k, j+1, m);
        if (j == l) {
            break;
        }
        int sz = j-i+1;
        int s = computeSum(sz-1);
        int subtract = 0;
        for (auto it = m.begin(); it != m.end(); it++) {
            printf("VAL %d, cnt %d start %d end %d\n", it->first, it->second.cnt, it->second.s, it->second.e);
            X x = it->second;
            int a = (x.s-i);
            int b = (j-x.e);
            if (a >= 1) {
                subtract += computeSum(a-1);
            }
            if (b >= 1) {
                subtract += computeSum(b-1);
            }
            // if (subOfElement.find(it->first) != subOfElement.end()) {
            //     subtract += subOfElement[it->first];
            // }
        }
        printf("I %d J %d RS %d subtract %d add %d FINAL %d\n", i, j, rs, subtract, s-subtract, rs + s - subtract);
        rs += s - subtract;
        i = decreaseSubArray(arr, k, i, m);
    }
    return rs;
}
int main() {
    // vector<int> arr = {1,2,3,4,5,6};
    // int k = 3;
    vector<int> arr = {3,2,2,1,2,2,2,1,1};
    int k = 3;

    // int l =(int)arr.size();
    // int i = 0;
    // int j = -1;
    // unordered_map<int, X> m;
    // while (true) {
    //     j = increaseSubArray(arr, k, j+1, m);
    //     for (auto it = m.begin(); it != m.end(); it++) {
    //         printf("VAL %d, cnt %d start %d end %d\n", it->first, it->second.cnt, it->second.s, it->second.e);
    //     }
    //     i = decreaseSubArray(arr, k, i, m);
    //     printf("I %d J %d\n", i, j);
    //     if (j == l) {
    //         break;
    //     }
    // }
    printf("%d\n", solve(arr, k));
    return 0;
}
