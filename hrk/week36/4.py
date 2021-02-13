import sys

def calculateSum(prev, now, h, p):
    if now == len(h)-1:
        return (now - prev) + p[prev]
    return abs(h[now] - h[prev]) + (now - prev) + p[prev]

def buildSegTree(h, tree, l ,r):
    if l == r:
        tree[l,r] = h[l]
        return tree[l,r]

    mid = (r-l)//2
    v1 = buildSegTree(h, tree, l, l+mid)
    v2 = buildSegTree(h, tree, l+mid+1, r)
    tree[l,r] = max(v1, v2)
    return tree[l,r]


def querySegTree(tree, l, r, start, stop):
    if r < start:
        return -1
    if l > stop:
        return -1
    if start <= l and r <= stop:
        return tree[l,r]
    mid = (r-l)//2
    v1 = querySegTree(tree, l, l+mid, start, stop)
    v2 = querySegTree(tree, l+mid+1, r, start, stop)
    return max(v1, v2)
                    

n = int(sys.stdin.readline()) + 1
x = int(sys.stdin.readline())
h = map(int, sys.stdin.readline().strip().split(' '))
p = map(int, sys.stdin.readline().strip().split(' '))

h = [x] + list(h) + [0]
p = [0] + list(p) + [0]

tree = {}
buildSegTree(h, tree, 0, len(h)-1)
dp = [None for _ in range(n)]
dp[0] = 0
dp[1] = calculateSum(0, 1, h, p)
for j in range(2, n):
    minV = None
    for i in range(j-1, -1, -1):
        maxH = querySegTree(tree, 0, len(h)-1, i, j-1)
        #print(maxH, h[i], i, j-1, dp)
        if maxH == h[i] or i == j-1:
            s = calculateSum(i, j, h, p)
            if minV == None or minV > dp[i] + s:
                minV = dp[i] + s
            if p[i] + abs(h[j]-h[i]) < 0: break
    dp[j] = minV



print(dp[-1])
