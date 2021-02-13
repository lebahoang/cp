import sys
import Queue
from sets import Set

def isOnlyZero(m):
  if m[0] > 0 and sum(m[1:]) == 0:
    return True
  return False
def isOnlyZeroAndOther(m):
  c = 0
  cc = 0
  for i in xrange(1,10):
    if m[i] > 0: c += 1
    cc += m[i]
  if m[0] > 1 and c == 1 and cc == 1:
    return True
  return False
def unmerge(src, dest):
  m = dest[:]
  for i in xrange(len(src)):
    m[src[i]] -= 1
  return m

def isPalindrome(m):
  if m[0] > 1 and sum(m[1:]) == 0:
    return False
  if m[0] > 1 and sum(m[1:]) < 2:
    return False
  c = 0
  for i in m:
    if i%2 == 1:
      c += 1
      if c > 1: return False
  return True

def find(arr, topLeft, bottomRight, hashtable):
  setO = Set()
  mem = {}
  currentMax = 0
  positionMax = None
  q = Queue.Queue()
  q.put((topLeft, bottomRight, hashtable))
  while not q.empty():
    item = q.get()
    i, j = item[0]
    ii, jj = item[1]
    tHashtable = item[2]
    #print q.qsize()
    area = (ii - i + 1)*(jj - j + 1)

    if isOnlyZero(tHashtable):
      if currentMax < 1:
        currentMax = 1
        positionMax = ((0,0), (0,0))
      continue

    if isOnlyZeroAndOther(tHashtable):
      if currentMax < 1:
        currentMax = 1
        positionMax = ((0,0), (0,0))
      continue

    if area <= currentMax:
      continue

    if isPalindrome(tHashtable):
      #print  item[0], item[1], tHashtable
      if currentMax < area:
        currentMax = area
        positionMax = (item[0], item[1])
  
    if i+1 <= item[1][0]:
      x = arr[i][j:jj+1]
      t = unmerge(x, tHashtable)
      if (i+1, j, ii, jj) not in setO:
        q.put(((i+1, j), item[1], t))
        setO.add((i+1, j, ii, jj))

    if j+1 <= item[1][1]:
      x = []
      for k in xrange(i, ii+1):
        x.append(arr[k][j])
      t = unmerge(x, tHashtable)
      if (i, j+1, ii, jj) not in setO:
        q.put(((i, j+1), item[1], t))
        setO.add((i, j+1, ii, jj))

    if ii-1 >= item[0][0]:
      x = arr[ii][j:jj+1]
      t = unmerge(x, tHashtable)
      if (i,j,ii-1,jj) not in setO:
        q.put((item[0], (ii-1, jj), t))
        setO.add((i,j,ii-1,jj))

    if jj-1 >= item[0][1]:
      x = []
      for k in xrange(i, ii+1):
        x.append(arr[k][jj])
      t = unmerge(x, tHashtable)
      #print 'dddddd', t, topLeft, (ii, jj-1)
      if (i,j,ii,jj-1) not in setO:
        q.put((item[0], (ii, jj-1), t))
        setO.add((i,j,ii,jj-1))

  return currentMax, positionMax

def solve(n, m, arr):
  hashtable = [0 for _ in xrange(10)]
  for i in xrange(n):
    for j in xrange(m):
      hashtable[arr[i][j]] += 1

  count, position = find(arr, (0,0), (n-1,m-1), hashtable)
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