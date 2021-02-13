#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

int solve(int n) {
	const int mod = 1e9+7;
	const int NMAX = 1e5 + 5;
	long long dp[NMAX][2][3];
	// memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	dp[0][0][1] = 1;
	dp[0][0][2] = 0;
	dp[0][1][0] = 1;
	dp[0][1][1] = 0;
	dp[0][1][2] = 0;

	for (int i = 1; i < n; i++) {
		dp[i][0][0] = (dp[i-1][0][0]%mod + dp[i-1][0][1]%mod + dp[i-1][0][2]%mod)%mod;
		dp[i][0][1] = (dp[i-1][0][0]%mod);
		dp[i][0][2] = (dp[i-1][0][1]%mod);
		dp[i][1][0] = (dp[i-1][1][0]%mod + dp[i-1][1][1]%mod + dp[i-1][1][2]%mod \
					  + dp[i-1][0][0]%mod + dp[i-1][0][1]%mod + dp[i-1][0][2]%mod)%mod;
		dp[i][1][1] = dp[i-1][1][0]%mod;
		dp[i][1][2] = dp[i-1][1][1]%mod;
	}
	long long rs = 0;
	for (int j = 0; j < 2; j++) {
		for (int k = 0; k < 3; k++) {
			// printf("%d %d %lld\n", j, k ,dp[n-1][j][k]);
			rs = (rs%mod + dp[n-1][j][k]%mod)%mod;
		}
	}
	return int(rs);
}

int main() {
	int n = 2;
	printf("%d\n", solve(n));
	return 0;
}