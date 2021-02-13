#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 1.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
struct I {
    int x;
    int y;
    int step;
    int cur_direction;
};
int main() {
    int t = 1;
    // cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n;
        cin >> n;
        int rs = 0;
        map<pair<int, pair<int, pair<int, int>>>, int> k;
        map<pair<int, int>, int> m;
        queue<I> q;
        q.push(I{0, 0, 0, -1});
        while (!q.empty()) {
            I i = q.front();
            q.pop();
            // printf("step %d\n", i.step);
            if (i.step == n) {
                if (m.find({i.x, i.y}) == m.end()) {
                    rs++;
                    m[{i.x, i.y}] = 1;
                }
            } else {
                if (i.cur_direction == -1) {
                    q.push(I{i.x+1, i.y, i.step+1, 0}); // north
                    q.push(I{i.x-1, i.y, i.step+1, 1}); // south
                    q.push(I{i.x, i.y-1, i.step+1, 2}); // west
                    q.push(I{i.x, i.y+1, i.step+1, 3}); // east
                } else if (i.cur_direction == 0) {
                    if (k.find({i.x, {i.y-1, {i.step+1, 3}}}) == k.end()) {
                        k[{i.x, {i.y-1, {i.step+1, 2}}}] = 1;
                        q.push(I{i.x, i.y-1, i.step+1, 2});
                    }
                    if (k.find({i.x, {i.y+1, {i.step+1, 2}}}) == k.end()) {
                        k[{i.x, {i.y+1, {i.step+1, 3}}}] = 1;
                        q.push(I{i.x, i.y+1, i.step+1, 3});
                    }
                } else if (i.cur_direction == 1) {
                    if (k.find({i.x, {i.y-1, {i.step+1, 3}}}) == k.end()) {
                        k[{i.x, {i.y-1, {i.step+1, 2}}}] = 1;
                        q.push(I{i.x, i.y-1, i.step+1, 2});
                    }
                    if (k.find({i.x, {i.y+1, {i.step+1, 2}}}) == k.end()) {
                        k[{i.x, {i.y+1, {i.step+1, 3}}}] = 1;
                        q.push(I{i.x, i.y+1, i.step+1, 3});
                    }
                } else if (i.cur_direction == 2) {
                    if (k.find({i.x-1, {i.y, {i.step+1, 1}}}) == k.end()) {
                        k[{i.x-1, {i.y, {i.step+1, 0}}}] = 1;
                        q.push(I{i.x-1, i.y, i.step+1, 0});
                    }
                    if (k.find({i.x+1, {i.y, {i.step+1, 0}}}) == k.end()) {
                        k[{i.x+1, {i.y, {i.step+1, 1}}}] = 1;
                        q.push(I{i.x+1, i.y, i.step+1, 1});
                    }
                } else {
                    if (k.find({i.x-1, {i.y, {i.step+1, 1}}}) == k.end()) {
                        k[{i.x-1, {i.y, {i.step+1, 0}}}] = 1;
                        q.push(I{i.x-1, i.y, i.step+1, 0});
                    }
                    if (k.find({i.x+1, {i.y, {i.step+1, 0}}}) == k.end()) {
                        k[{i.x+1, {i.y, {i.step+1, 1}}}] = 1;
                        q.push(I{i.x+1, i.y, i.step+1, 1});
                    }
                }
            }
        }
        printf("%d\n", rs);
    }
    
    return 0;
}