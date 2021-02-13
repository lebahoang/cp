import sys


def method(n, arr):
  r = 0
  while arr:
    B = []
    for i in xrange(n):
      for j in xrange(n):
        # print arr[i], arr[j]
        if arr[i] != arr[j]:
          B.append(abs(arr[i] - arr[j]))
    arr = B[:]
    n = len(arr)
    if n > 10**5:
      r = -1
      break
    r += 1
  return r

n = int(sys.stdin.readline())
arr = map(int,sys.stdin.readline().strip().split(' '))
print method(n,arr)
