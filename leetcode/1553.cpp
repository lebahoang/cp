#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

unordered_map<int, int> f;
int dfs(int n) {
	if (n == 0) {
		return 0;
	}
	auto v = f.find(n);
	if (v != f.end()) {
		return v->second;
	}
	int t = min(1+n%2+dfs(n/2), 1+n%3+dfs(n/3));
	// printf("AAAAA %d %lu\n", n, f.size());
	f[n] = t;
	return t;
}

void go(long long n) {
	int dp[35][35];
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			dp[i][j] = 2e9;
		}
	}
	dp[1][0] = 2;
	dp[0][1] = 2;
	long long x = 1;
	for (int i = 0; i < 32; i++) {
		if (i > 0) {
			x = x*2;
		}
		long long y = 1;
		for (int j = 0; j < 32; j++) {
			if (j > 0) {
				y = y*3;
			}
			if (x*y > n) {
				break;
			}
			if (i-1 >= 0) {
				dp[i][j] = min(dp[i][j], 1+dp[i-1][j]);
			}
			if (j-1 >= 0) {
				dp[i][j] = min(dp[i][j], 1+dp[i][j-1]);
			}
			f[int(x*y)] = dp[i][j];
		}
	}
}
int solve(int n) {
	if (n == 2 || n == 3) {
		return 2;
	}
	long long nn = n;
	go(nn);
    return dfs(n);
}

int main() {
	// printf("%d\n", solve(10000000));
	printf("%d\n", solve(182));
	return 0;
}