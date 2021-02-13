#include <cstdio>
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

int minMoves(vector<int> arr) {
    int n = (int)arr.size();
    int i = 0;
    queue<int> q1;
    queue<int> q2;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            q1.push(i);
        }
        if (arr[n-i-1] == 1) {
            q2.push(n-i-1);
        }
    }
    int rs = 0;
    while (i < n && !q1.empty()) {
        if (arr[i] != 1) {
            int k = q1.front();
            q1.pop();
            printf("i %d k %d\n", i, k);
            rs += k-i;
            arr[k] = 0;
        } else {
            q1.pop();
        }
        i++;
    }
    int rs2 = 0;
    i = n-1;
    while (i >= 0 && !q2.empty()) {
        if (arr[i] != 1) {
            int k = q2.front();
            q2.pop();
            rs2 += i-k;
            arr[k] = 0;
        } else {
            q2.pop();
        }
        i--;
    }
    printf("%d %d\n", rs, rs2);
    return min(rs, rs2);
}

int main() {
    // printf("%d\n", minMoves({1,0,1,0,0,0,0,1}));
    printf("%d\n", minMoves({1,1,1,1,0,1,0,1}));
    return 0;
}