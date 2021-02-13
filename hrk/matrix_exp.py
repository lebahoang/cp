import sys
mod = 10**9 + 7
def calculateFirstValues(arr, K):
	dp = [0]*(K+1)
	for i in arr:
	dp[i] = 1
	for i in xrange(1, K+1):
	for j in arr:
		if i-j > 0:
		dp[i] += dp[i-j]
	return dp[1:]
def getInitMatrix(arr, K): # array of first 15 values
	F = []
	for i in arr:
	F.append([i])
	return F
def getExponentialMatrix(arr, K): # array of first 15 values
	M = []
	for i in xrange(K-1):
	M.append([0]*K)
	M[-1][i+1] = 1
	M.append([0]*K)
	for i in arr:
	M[-1][K-i] = 1
	return M
def mulMatrix(M, F):
	n = len(M)
	m = len(F[0])
	rs = [[0 for _ in xrange(m)] for _ in xrange(n)]

	for i in xrange(n):
	for j in xrange(m):
		for l in xrange(n):
		rs[i][j] = (rs[i][j]%mod + (M[i][l]*F[l][j])%mod)

	return rs
def matrixPower(M, times):
	if times == 1:
	return M

	if times%2 == 1:
	return mulMatrix(M, matrixPower(M ,times-1))
	kk = matrixPower(M, times/2)
	return mulMatrix(kk, kk)



n = int(sys.stdin.readline().strip())
k = int(sys.stdin.readline().strip())
K = 15
arr = map(int, sys.stdin.readline().strip().split(' '))
a = calculateFirstValues(arr, 15)
F = getInitMatrix(a, K)
M = getExponentialMatrix(arr, K)


if n-15 > 0:
	MM = matrixPower(M, n-15)
	FN = mulMatrix(MM, F)
	print (FN[-1][0]*2)%mod
else:
	print (F[n-1][0]*2)%mod	