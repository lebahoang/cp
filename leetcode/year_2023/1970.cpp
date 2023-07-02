#include <iostream>
#include <random>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1970.cpp && ./s.out


void initDisjoinSet(int n, vector<int>& p, vector<int>& rankAtNode) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
        rankAtNode[i] = 0;
    }
}

int findSubset(int x, vector<int>& p) {
    // apply path compression
    // which is the idea: moving the sub tree rooted at x to be a child of root node
    if (x == p[x]) {
        return x;
    }
    p[x] = findSubset(p[x], p);
    return p[x];
}

void union2Subsets(int x, int y, vector<int>& p, vector<int>& rankAtNode) {
    // apply union by rank
    // which is the idea: attach the smaller-depth tree into the bigger depth tree
    // more specifically the root node of smaller tree will become a child of the root node
    // of bigger tree
    int xroot = findSubset(x, p);
    int yroot = findSubset(y, p);
    if (xroot == yroot) {
        return;
    }
    if (rankAtNode[xroot] >= rankAtNode[yroot]) {
        p[yroot] = xroot;
        if (rankAtNode[xroot] == rankAtNode[yroot] ) {
            rankAtNode[xroot]++;
        }
    } else if (rankAtNode[xroot] < rankAtNode[yroot]) {
        p[xroot] = yroot;
    }
}

int bs(int val, vector<int>& arr) {
    int n = arr.size();
    if (arr[n-1] <= val) {
        return n-1;
    }
    if (arr[0] >= val) {
        return 0;
    }
    int l = 0;
    int r = n-1;
    while (l <= r) {
        int mid = (l+r)/2;
        if (arr[mid] < val && arr[mid+1] >= val) {
            return mid;
        } else if (arr[mid] >= val) {
            r = mid-1;
        } else {
            l = mid+1;
        }
    }
    return -1;
}

int solve(int r, int c, vector<vector<int>>& cells) {
    int n = cells.size();
    vector<int> p(n+1, 0);
    vector<int> rankAtNode(n+1, 0);
    vector<vector<int>> mat(r, vector<int>(c, -1));
    vector<int> colZero = {};
    vector<int> colN = {};
    for (int i = 0; i < n; i++) {
        int a = cells[i][0]-1;
        int b = cells[i][1]-1;
        mat[a][b] = i;
        if (b == 0) {
            colZero.push_back(i);
        } else if (b == c-1) {
            colN.push_back(b);
        }
    }
    int day1 = -1;
    int day2 = -1;
    for (int& val: colN) {
        int ind = bs(val, colZero);
        if (ind > -1) {
            day1 = colZero[ind];
            day2 = val;
        }
    }
    initDisjoinSet(n, p, rankAtNode);
    vector<vector<int>> d = {
        {-1, 0},{1, 0},{0, -1},{0, 1},
        {-1, 1},{-1, 1},{1, -1},{1, 1}
    };
    for (int i = 0; i < n; i++) {
        int a = cells[i][0]-1;
        int b = cells[i][1]-1;
        if (i < day1) {
            
        } 
    }
} 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    return 0;
}