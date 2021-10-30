#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
int dp[302][302];

dp[i][j][k] <-- dp[0][0][0]
dp[i][j][k] = dp[i-1][j][k]*(i/(i+j+k))
int main() {

    return 0;
}