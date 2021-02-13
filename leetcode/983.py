def get_ind(days, date):
    for i in range(len(days)-1, -1, -1):
        if days[i] <= date:
            return i
    return -1
def solve983(days, costs):
    n = len(days)
    dp = [10**9]*n
    for i in range(n):
        k = get_ind(days, days[i]-1)
        if k < 0:
            dp[i] = min(dp[i], costs[0])
        else:
            dp[i] = min(dp[i], dp[k]+costs[0])

        k = get_ind(days, days[i]-7)
        if k < 0:
            dp[i] = min(dp[i], costs[1])
        else:
            dp[i] = min(dp[i], dp[k]+costs[1])

        k = get_ind(days, days[i]-30)
        if k < 0:
            dp[i] = min(dp[i], costs[2])
        else:
            dp[i] = min(dp[i], dp[k]+costs[2])
    return dp[n-1]

days = [3]
costs = [2,7,15]
print(solve983(days, costs))


