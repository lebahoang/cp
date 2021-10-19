#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;
struct I {
    int pos;
    int speed;
    int c;
    string path;
};
pair<int, string> dfs(int target, int pos, int speed, int low, int upper, map<string, pair<int, string>>& dp) {
    string key = to_string(pos) + "_" + to_string(speed);
    if (dp.find(key) != dp.end()) {
        return dp[key];
    }
    if (pos == target) {
        // printf("dp[%s] %d, %s\n", key.c_str(), dp[key].first, dp[key].second.c_str());
        dp[key] = {0, ""};
        return dp[key];
    }
    dp[key] = {1e8, ""};
    if (pos + speed <= upper && pos + speed >= low) {
        auto t = dfs(target, pos+speed, speed*2, low, upper, dp);
        if (t.first+1 < dp[key].first) {
            dp[key].first = t.first+1;
            dp[key].second = "A" + t.second;
        }
    }
    if (speed >= 0) {
        auto t = dfs(target, pos, -1, low, upper, dp);
        if (t.first+1 < dp[key].first) {
            dp[key].first = t.first+1;
            dp[key].second = "R" + t.second;
        }
    } else {
        auto t = dfs(target, pos, 1, low, upper, dp);
        if (t.first+1 < dp[key].first) {
            dp[key].first = t.first+1;
            dp[key].second = "R" + t.second;
        }
    }
    // printf("dp[%s] %d, %s\n", key.c_str(), dp[key].first, dp[key].second.c_str());
    return dp[key];
}

// int bfs(int target, int low, int upper) {
//     unordered_map<string, int> m;
//     int rs = 1e9;
//     queue<I> q;
//     q.push(I{0,1,0});
//     while (!q.empty()) {
//         I i = q.front();
//         q.pop();
//         string key = to_string(i.pos) + "_" + to_string(i.speed);
//         m[key] = 1;
//         if (i.pos == target) {
//             return i.c;
//         }
//         // if (i.c > rs) continue;
//         if (i.speed >= 0) {
//             string k = to_string(i.pos) + "_" + to_string(-1);
//             if (m.find(k) == m.end()) {
//                 // q.push(I{i.pos, -1, i.c+1, "R"+i.path});
//                 q.push(I{i.pos, -1, i.c+1});
//             }     
//         } else {
//             string k = to_string(i.pos) + "_" + to_string(1);
//             if (m.find(k) == m.end()) {
//                 q.push(I{i.pos, 1, i.c+1});
//             } 
//         }
//         if (i.pos + i.speed <= upper && i.pos + i.speed >= low) {
//             string k = to_string(i.pos+i.speed) + "_" + to_string(i.speed*2);
//             if (m.find(k) == m.end()) {
//                 q.push(I{i.pos+i.speed, i.speed*2, i.c+1});
//             }
//         }
        
//     }
//     return rs;
// }

int bfs(int target, int low, int upper) {
    int rs = 1e9;
    queue<I> q;
    q.push(I{0,1,0});
    while (!q.empty()) {
        I i = q.front();
        q.pop();
        if (i.pos == target) {
            return i.c;
        }
        // if (i.c > rs) continue;
        if (i.speed >= 0 && i.pos + i.speed > target) {
            q.push(I{i.pos, -1, i.c+1});
        } else if (i.speed < 0 && i.pos + i.speed < target) {
            q.push(I{i.pos, 1, i.c+1});
        }
        if (i.pos + i.speed <= upper && i.pos + i.speed >= low) {
            q.push(I{i.pos+i.speed, i.speed*2, i.c+1});
        }
    }
    return rs;
}

int main() {
    int target = 3456;
    // printf("%d\n", solve(target));
    // map<string, pair<int, string>> dp;
    // auto t = dfs(target, 0, 1, -3*target, 3*target, dp);
    // printf("%d %s\n", t.first, t.second.c_str());
    printf("%d\n", bfs(target, 0, 2*target));
    return 0;
}