def solve(step, length):
    mod = 10**9+7
    dp = [[0 for _ in range(step+3)] for _ in range(min(step+5, length))]
    dp[0][0] = 1
    for i in range(1, step+1):
        for j in range(min(step, length)):
            if j-1 >= 0:
                dp[j][i] = (dp[j][i]%mod + dp[j-1][i-1]%mod)%mod
            if j+1 < min(step, length):
                dp[j][i] = (dp[j][i]%mod + dp[j+1][i-1]%mod)%mod
            dp[j][i] = (dp[j][i]%mod + dp[j][i-1]%mod)%mod
            print(j,i,dp[j][i])
    return dp[0][step]

print(solve(4, 2))