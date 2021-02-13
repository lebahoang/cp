import sys

def isIncreasing(ints, y1, y2):
  if y1 == y2:
    return True
  a = search1(ints, y1, 0, len(ints)-1)
  b = search1(ints, y2, 0, len(ints)-1)

  if a == b:
    return True
  return False


def search1(arr, v, left, right):
  if left > right:
    if v <= arr[0]:
      return 0
    elif v >= arr[-1]:
      return len(arr)-1
    return None

  mid = (left + right)/2
  if arr[mid] == v:
    return mid
  if mid-1 >= 0 and v > arr[mid-1] and v < arr[mid]:
    return mid-1
  if v > arr[mid]:
    return search1(arr, v, mid+1, right)
  return search1(arr, v, left, mid-1)

def search2(arr, v, left, right):
  if left > right:
    if v <= arr[0]:
      return 0
    elif v >= arr[-1]:
      return len(arr)-1
    return None

  mid = (left + right)/2
  if mid-1 >= 0 and v >= arr[mid-1] and v < arr[mid]:
    return mid-1
  if v >= arr[mid]:
    return search2(arr, v, mid+1, right)
  return search2(arr, v, left, mid-1)

def getIntervals(arr, n, m):
  rs = []
  for i in xrange(n):
    j = 1
    ints = [0]
    while j < m:
      if arr[i][j] < arr[i][j-1]:
        ints.append(j)
      j += 1

    rs.append(ints)
  return rs
n,m = map(int, sys.stdin.readline().strip().split(' '))
arr = []
for _ in xrange(n):
  a = map(int, sys.stdin.readline().strip().split(' '))
  arr.append(a)

ints = getIntervals(arr, n, m)
total = 0
for y1 in xrange(m):
  for y2 in xrange(y1, m):
    #print y1, y2
    c = 0
    for i in xrange(n):
      if isIncreasing(ints[i], y1, y2):
        if i-1 >= 0:
          if arr[i][y1] >= arr[i-1][y2]:
            c += 1
          else:
            total += c*(c+1)/2
            #print 'x', y1,y2,c,i
            c = 1
        else:
          c += 1
      else:
        total += c*(c+1)/2
        #print 'y', y1,y2,c,i
        c = 0
    if c > 0:
      total += c*(c+1)/2
      #print 'z', y1,y2,c
    #print '-----'

print total


