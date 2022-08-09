#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out

vector<int> zigzagTraverse(vector<vector<int>> a) {
  int t = 1;
  int n = (int)a.size();
  int m = (int)a[0].size();
  printf("N %d M %d\n", n, m);
  vector<int> rs = {};
  vector<int> b = {};
  for (int i = 0; i < n; i++) {
    int j = 0;
    for (int x = i; x >= 0; x--) {
      b.push_back(a[x][j]);
      j++;
    }
    if (t%2 == 0) {
      for (int& x: b) {
        rs.push_back(x);
      }
    } else {
      for (auto x = b.rbegin(); x != b.rend(); x++) {
        rs.push_back(*x);
      }
    }
    b.clear();
    t++;
  }
  printf("dsadas\n");
  for (int j = 1; j < m; j++) {
    int i = n-1;
    for (int x = j; x < m; x++) {
      if (i < 0) break;
      b.push_back(a[i][x]);
      i--;
    }
    printf("J %d\n", j);
    if (t%2 == 0) {
      for (int& x: b) {
        rs.push_back(x);
      }
    } else {
      for (auto x = b.rbegin(); x != b.rend(); x++) {
        rs.push_back(*x);
      }
    }
    b.clear();
    t++;
  }
  return rs;
}


int main() {
    vector<int> rs = zigzagTraverse({
      {1, 3,  4,  10, 13, 12},
      {2, 5,  9,  11, 14, 12},
      {6, 8,  12, 15, 15, 49},
      {7, 13, 14, 16, 20, 20}
    });
    for (int& x: rs) {
      printf("%d ", x);
    }
    printf("\n");
}