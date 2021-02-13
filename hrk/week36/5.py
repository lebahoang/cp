import sys

def getReduceRangeHorizontally(arr, k, i, j):
	stop = min(j+k, len(arr[0])-1)

	minV = None
	b = -1
	c = 0
	for m in range(j, stop+1):
		c += arr[i][m]
		if minV == None or minV > c:
			minV = c
			b = m

	return (i, j, b)

def getReduceRangeVertically(arr, k, i, j):
	stop = min(i+k, len(arr)-1)

	minV = None
	b = -1
	c = 0
	for m in range(i, stop+1):
		c += arr[m][j]
		if minV == None or minV > c:
			minV = c
			b = m

	return (j, i, b)

def getPositionsHorizontally(arr, i, j, b):
	rs = []
	for k in range(j, b+1):
		rs.append(arr[i][k])
	return rs

def getPositionsVertically(arr, j, i, b):
	rs = []
	for k in range(i, b+1):
		rs.append(arr[k][j])
	return rs

def replacePositionsHorizontally(arr, i, j, b, replacer):
	for k in range(len(replacer)):
		arr[i][j+k] = replacer[k]

def replacePositionsVertically(arr, j, i, b, replacer):
	for k in range(len(replacer)):
		arr[i+k][j] = replacer[k]

def findMaxSumSubArray(arr):
  maxV = [-1]*len(arr)
  maxV[0] = arr[0]
  c = arr[0]
  for i in range(1, len(arr)):
    if c+arr[i] > 0:
      c += arr[i]
    else:
      c = 0
    if c > 0:
      maxV[i] = max(maxV[i-1], arr[i], c)
    else:
      maxV[i] = max(maxV[i-1], arr[i])
  return maxV[len(arr)-1]


def findSums(arr, n, m):
	sums = []
	for i in range(n):
		t = []
		c = 0
		for j in range(m):
			c += arr[i][j]
			t.append(c)
		sums.append(t)
	return sums

def findMaxSumSubMatrix(arr, n, m):
	sums = findSums(arr, len(arr), len(arr[0]))
	maxV = None
	for j1 in range(n[0], n[1]+1):
		for j2 in range(m[0], m[1]+1):
			s = []
			for i in range(len(arr)):
				v = 0
				if j1-1 < 0:
					v = sums[i][j2]
				else:
					v = sums[i][j2] - sums[i][j1-1]
				s.append(v)

			vv = findMaxSumSubArray(s)
			if maxV == None or maxV < vv: maxV = vv
	return maxV

def solve(arr, n, m, k):
	maxV = None
	minItem = None
	minItemPos = None


	total = 0
	for ii in range(n):
		for jj in range(m):
			if arr[ii][jj] < 0:
				i, j, b = getReduceRangeHorizontally(arr, k, ii, jj)
				x = getPositionsHorizontally(arr, i, j, b)
				replacePositionsHorizontally(arr, i, j, b, [0]*len(x))
				v = findMaxSumSubMatrix(arr, (0,j), (b, m-1))
				#print('x', i, j, x, v, arr)
				replacePositionsHorizontally(arr, i, j, b, x)
				if maxV == None or maxV < v:
					maxV = v



				j, i, b = getReduceRangeVertically(arr, k, ii, jj)
				y = getPositionsVertically(arr, j, i, b)
				replacePositionsVertically(arr, j, i, b, [0]*len(y))
				v = findMaxSumSubMatrix(arr, (0, j), (j, m-1))
				#print('y', i, j, y, v, arr)
				replacePositionsVertically(arr, j, i, b, y)
				if maxV == None or maxV < v:
					maxV = v
			else:
				if minItem == None or minItem > arr[ii][jj]:
					minItem = arr[ii][jj]
					minItemPos = (ii, jj)
				total += arr[ii][jj]

	if maxV == None:
		return total - arr[minItemPos[0]][minItemPos[1]]
	return maxV


n,m,k = map(int, sys.stdin.readline().strip().split())
arr = []
for _ in range(n):
	t = list(map(int, sys.stdin.readline().strip().split()))
	arr.append(t)

print(solve(arr, n, m, k))