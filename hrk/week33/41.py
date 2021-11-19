import sys

def merge(src, dest):
  x = dest[:]
  for i in xrange(10):
    x[i] = dest[i] + src[i]
  return x
def unmerge(src, dest):
  m = dest[:]
  for i in xrange(len(src)):
    m[src[i]] -= 1
  return m

def isPalindrome(m):
  if m[0] > 1 and sum(m[1:]) < 2:
    return False
  c = 0
  for i in m:
    if i%2 == 1:
      c += 1
      if c > 1: return False
  return True

def find(mem, arr, topLeft, bottomRight, hashtable, currentMax):
  i, j = topLeft
  ii, jj = bottomRight
  if (ii - i + 1)*(jj - j + 1) <= currentMax:
    return None, None, None
  if (i, j, ii, jj) in mem:
    # print topLeft, bottomRight, hashtable
    area = mem[i,j,ii,jj]
    return area, (topLeft, bottomRight), area

  if isPalindrome(hashtable):
    if hashtable[0] > 1 and sum(hashtable[1:]) == 0:
      area = 1
    else:
      area = (ii - i + 1)*(jj - j + 1)
    mem[i, j, ii, jj] = area
    return area, (topLeft, bottomRight), area

  a = b = c = d = 0
  positionA = positionB = positionC = positionD = None
  if i+1 <= bottomRight[0]:
    x = arr[i][j:jj+1]
    t = unmerge(x, hashtable)
    a, positionA, currentMax = find(mem, arr, (i+1, j), bottomRight, t, currentMax)
    if a is None: a = 0

  if j+1 <= bottomRight[1]:
    x = []
    for k in xrange(i, ii+1):
      x.append(arr[k][j])
    t = unmerge(x, hashtable)
    b, positionB, currentMax = find(mem, arr, (i, j+1), bottomRight, t, currentMax)
    if b is None: b = 0

  if ii-1 >= topLeft[0]:
    x = arr[ii][j:jj+1]
    t = unmerge(x, hashtable)
    c, positionC, currentMax = find(mem, arr, topLeft, (ii-1, jj), t, currentMax)
    if c is None: c = 0

  if jj-1 >= topLeft[1]:
    x = []
    for k in xrange(i, ii+1):
      x.append(arr[k][jj])
    t = unmerge(x, hashtable)
    d, positionD, currentMax = find(mem, arr, topLeft, (ii, jj-1), t, currentMax)
    if d is None: d = 0

  positionMax = None
  maxV = 0
  rs = [a,b,c,d]
  rs1 = [positionA, positionB, positionC, positionD]
  for k in xrange(4):
    if maxV < rs[k]:
      maxV = rs[k]
      positionMax = rs1[k]

  mem[i,j,ii,jj] = maxV
  currentMax = maxV
  return maxV, positionMax, currentMax

def solve(n, m, arr):
  d = {}
  hashtable = [0 for _ in xrange(10)]
  for i in xrange(n):
    for j in xrange(m):
      hashtable[arr[i][j]] += 1

  count, position, currentMax = find(d, arr, (0,0), (n-1,m-1), hashtable, 0)
  if count == 1: position = ((0,0),(0,0))

  return count, '%d %d %d %d' %(position[0][0], position[0][1], position[1][0], position[1][1])

sys.setrecursionlimit(100000)
n, m = map(int, sys.stdin.readline().strip().split(' '))
arr = []
for _ in xrange(n):
  x = map(int, sys.stdin.readline().strip().split(' '))
  arr.append(x)

count, string = solve(n, m, arr)
print count
print string