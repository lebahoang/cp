import sys

def get_max_from_i(arr, i, w):
	dp = [[0 for jj in range(w+1)] for j in range(len(arr))]
	for j in range(i, len(arr)):
		dp[j][arr[j]] = 1
		for m in range(1,w+1):
			if j-1 >= i:
				dp[j][m] += dp[j-1][m]
				if m-arr[j] > 0 and dp[j-1][m-arr[j]] > 0:
					dp[j][m] += dp[j-1][m-arr[j]]


	c = -1
	for j in range(i, len(arr)):
		for m in range(1,w+1):
			if c == -1 or c < dp[j][m]: c = dp[j][m]
	return c

t = int(sys.stdin.readline().strip())
for case in range(t):
	n = int(sys.stdin.readline().strip())
	arr = list(map(int, sys.stdin.readline().strip().split(' ')))
	arr = arr[::-1]
	


