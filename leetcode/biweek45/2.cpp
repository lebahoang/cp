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

// g++ -std=c++14 -O2 -o s.out 2.cpp && ./s.out
using namespace std;
using ll = long long;
int search(int end, vector<vector<int>>& events, int i, int n) {
    int l = i;
    int r = n-1;
    while (true) {
        if (l > r) break;
        int mid = (l+r)/2;
        if (events[mid][0] > end && events[mid-1][0] <= end) {
            return mid;
        } else if (events[mid][0] <= end) {
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    return -1;
}
// vector<vector<ll>> solve(vector<vector<int>>& events, int k) {
int solve(vector<vector<int>>& events, int k) {
    int n = events.size();
    sort(events.begin(), events.end(), [&](vector<int> a, vector<int> b){
        if (a[0] < b[0]) return true;
        else if (a[0] > b[0]) return false;
        return a[1] < b[1];
    });
    // for (vector<int> x: events) {
    //     printf("%d %d %d\n", x[0], x[1], x[2]);
    // }
    vector<int> next_event(n+1, -1);
    for (int i = 0; i < n; i++) {
        int ind = search(events[i][1], events, i+1, n);
        next_event[i] = ind;
    }
    vector<vector<ll>> dp(n+1, vector<ll>(k+1, 0));
    ll rs = 0;
    for (int j = 1; j <= k; j++) {
        for (int i = 0; i < n; i++) {
            int ind = next_event[i];
            if (j == 1) {
                dp[i][j] = events[i][2];
                rs = max(rs, dp[i][j]);
            } else {
                if (ind >= 0) {
                    // if (ind == 5 && j == 2) printf("ind %d, j %d, i %d, dp %lld\n", ind, j, i, dp[ind][j]);
                    for (int x = ind; x < n; x++) {
                        if (dp[i][j-1] > 0) {
                            dp[x][j] = max(dp[x][j], dp[i][j-1] + events[x][2]);
                            rs = max(rs, dp[x][j]);
                        }
                    }
                }
            }
        }
    }
    // return dp;
    return (int)rs;
}
vector<vector<ll>> bf(vector<vector<int>>& events, int k) {
    int n = events.size();
    sort(events.begin(), events.end(), [](vector<int>& a, vector<int>& b){
        if (a[0] < b[0]) return true;
        else if (a[0] > b[0]) return false;
        return a[1] < b[1];
    });
    // for (vector<int> x: events) {
    //     printf("%d %d %d\n", x[0], x[1], x[2]);
    // }
    vector<vector<ll>> dp(n+1, vector<ll>(k+1, 0));
    ll rs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j == 1) {
                dp[i][j] = events[i][2];
            } else {
                ll t = -1e12+7;
                for (int x = 0; x <= i-1; x++) {
                    if (events[x][1] < events[i][0] && dp[x][j-1] > t) t = dp[x][j-1];
                }
                if (t > 0) dp[i][j] = t + events[i][2];
            }
            rs = max(rs, dp[i][j]);
        }
    }
    // return rs;
    return dp;
}
int main() {
    // vector<vector<int>> events = {{1,2,400},{2,3,100},{3,4,300},{5,6,7},{7,8,9}};
    // int k = 2;
    // vector<vector<int>> events = {{87,95,42}, {3,42,37}, {20,42,100}, {53,84,80}, {10,88,38}, {25,80,57}, {18,38,33}};
    // int k = 3;
    vector<vector<int>> events = {
        {54170800,836041799,244661},
        {54182206,101984119,150555},
        {58400134,787360507,799140},
        {81227374,667880478,548610},
        {106125069,235256263,351626},
        {106176502,513676326,558956},
        {106781093,240262675,926872},
        {118634190,931640112,904912},
        {147846768,194998968,612755},
        {148450400,967146428,484818},
        {237054158,906310709,713262},
        {239861818,464023963,967213},
        {240174579,745765947,661637},
        {241736797,338332143,899174},
        {280547465,625935474,645311},
        {293949039,390072060,496867},
        {330211034,558316871,338254},
        {330939193,441251629,47919},
        {351807846,540280427,341186},
        {373554802,993976326,671447},
        {459929075,951919511,721143},
        {554895182,796542604,423196},
        {581966620,828402338,818217},
        {589225674,785367284,501891},
        {664550832,931830805,731120},
        {748091027,871685606,212743},
        {941444720,951429172,939290},
    };
    int k = 10;
    printf("%d\n", solve(events, k));
    // auto dp1 = solve(events, k);
    // auto dp2 = bf(events, k);
    // for (int i = 0; i < (int)events.size(); i++) {
    //     for (int j = 1; j <= k; j++) {
    //         if (dp1[i][j] != dp2[i][j]) {
    //             printf("i %d, j %d, %lld %lld\n", i, j, dp1[i][j], dp2[i][j]);
    //             break;
    //         }
    //     }
    // }
    //printf("%d %d\n", , bf(events, k));
    // vector<vector<int>> events = {{1,100,100}, {2,2,2}, {3,30,3},{4,4,4},{5,5,5},{6,6,6},{7,7,7}};
    // printf("%d\n", find(6, events, (int)events.size()));

    return 0;
}