import sys


n = int(sys.stdin.readline().strip())
hs = list(map(int, sys.stdin.readline().strip().split(' ')))


dp = [0]*n

for i in range(1, n):
    x = 10**10
    if i-1 >= 0:
        x = min(x, dp[i-1]+abs(hs[i]-hs[i-1]))
    if i-2 >= 0:
        x = min(x, dp[i-2]+abs(hs[i]-hs[i-2]))
    dp[i] = x
print(dp[n-1])