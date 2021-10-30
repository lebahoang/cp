import sys

n,w = map(int, sys.stdin.readline().strip().split(' '))
arr = []
for _ in range(n):
    wi, vi = map(int, sys.stdin.readline().strip().split(' '))
    arr.append((wi, vi))

dp = [-1 for i in range(w+1)]
t = [-1 for j in range(w+1)]
for i in range(n):
    for j in range(1, w+1):
        if j-arr[i][0] >= 1 and dp[j-arr[i][0]] != -1:
            # print(j, j-arr[i][0], t[j], dp[j-arr[i][0]]+arr[i][1], dp[j-arr[i][0]])
            t[j] = max(t[j], dp[j-arr[i][0]]+arr[i][1])
    t[arr[i][0]] = max(t[arr[i][0]], arr[i][1])

    for j in range(1, w+1):
        dp[j] = max(dp[j], t[j])
        t[j] = -1
# print(dp)
print(max(dp))