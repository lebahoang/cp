import sys

def findInit(arr, m):
  c = 0
  for i in xrange(m):
    for j in xrange(i):
      if arr[i] < arr[j]:
        c += 1
  return c

def getBefore(arr, i, m):
  rs = 0
  for j in xrange(i-1, i-m,-1):
    if arr[i] < arr[j]:
      rs += 1
  return rs

def getAfter(arr, i, m):
  rs = 0
  for j in xrange(i+1, i+m):
    if arr[i] > arr[j]:
      rs += 1
  return rs
n,m = map(int, sys.stdin.readline().strip().split(' '))
arr = map(int, sys.stdin.readline().strip().split(' '))


c = findInit(arr, m)
total = c
for i in xrange(m, n):
  a = getBefore(arr, i, m)
  b = getAfter(arr, i-m, m)
  c = c + a - b
  total += c

print total