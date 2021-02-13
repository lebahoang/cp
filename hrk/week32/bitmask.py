import sys

#count subset
def ex1(arr, value):
  n = len(arr)
  rs = 0
  for i in range(2**n):
    x = bin(i)[2:]
    x = '0'*(n-len(x))+x
    print(i, x)
    sum = 0
    for j in range(len(x)):
      if x[j] == '1':
        sum += arr[j]
    if sum >= value:
      rs += 1
  print('------------')
  return rs

def ex2(n, prices):
  def findMin(dp, mask, n, prices, item):
    if item == n:
      dp[mask, item] = 0
      return 0
    if (mask, item) in dp:
      return dp[mask, item]

    t = -1
    m = bin(mask)[2:]
    m = '0'*(n-len(m)) + m
    for k in range(n):
      if m[n-1-k] == '0':
        xx = findMin(dp, mask | 1 << k, n, prices, item+1) + prices[k][item]
        if t == -1 or t > xx: t = xx
    dp[mask, item] = t
    return t

  dp = {}
  rs = findMin(dp, 0, n, prices, 0)
  print(dp)
  return rs


def findMinimumWithGivenConfiguration(dp, mask, n, v, links, node, start):
  if mask == 2**n-1:
    for k in v[node]:
      if k == start:
        dp[mask] = 1
        return links[node, start]
    return -1
  if (mask, node) in dp:
    return dp[mask, node]
  t = -1
  m = bin(mask)[2:]
  m = '0'*(n-len(m)) + m
  for k in v[node]:
    kk = k-1
    if m[n-1-kk] == '0':
      xx = findMinimumWithGivenConfiguration(dp, mask | 1 << kk, n, v, links, k, start)
      if xx > -1:
        xx += links[node, k]
      #print('hhh', xx, mask | 1 << kk, m, (mask,node))
      if t == -1 or t > xx: t = xx
  dp[mask, node] = t
  return t

def ex3():
  import sys
  n,m = map(int, sys.stdin.readline().strip().split())
  v = [[] for _ in range(n+1)]
  links = {}
  for _ in range(m):
    x,y,z = map(int, sys.stdin.readline().strip().split())
    v[x].append(y)
    v[y].append(x)
    links[x,y] = z
    links[y,x] = z

  mask = 0
  t = -1
  for node in range(1, n+1):
    dp = {}
    xx = findMinimumWithGivenConfiguration(dp, mask | 1 << node-1, n, v, links, node, node)
    #print('fdsf', mask | 1 << node-1, xx)
    if 2**n-1 in dp and xx > -1:
      #print('vo', dp)
      if t == -1 or t > xx: t = xx
  print(t)





#print(ex1([20,3,100], 123))
# prices = [
#     [1,22,33,123],
#     [11,22,44,56],
#     [111,2,333,67],
#     [1,1,1,1]
#   ]

# n = len(prices)
# print(ex2(n, prices))
ex3()

