import sys

n = int(sys.stdin.readline().strip())
arr = []
for _ in range(n):
    a,b,c = map(int, sys.stdin.readline().strip().split(' '))
    arr.append((a,b,c))


dp = [[-1, -1, -1] for _ in range(n)]
dp[0][0] = arr[0][0]
dp[0][1] = arr[0][1]
dp[0][2] = arr[0][2]
for i in range(1,n):
    dp[i][0] = max(dp[i-1][1], dp[i-1][2]) + arr[i][0]
    dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + arr[i][1]
    dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + arr[i][2]

print(max(dp[n-1]))

