import sys

def applyState(arr, i, step):
  for s in xrange(step):
    t = arr[i-1]
    arr[i-1] = arr[i]
    arr[i] = t
    i -= 1
  return arr

def getMore(arr, i):
  c = 0
  for j in xrange(i+1, len(arr)):
    if arr[j] < arr[i]:
      c += 1
  return c
def solve(n, arr):
  x = [i for i in xrange(1,n+1)]
  c = 0
  for i in xrange(n):
    if arr[i] > i+1 and arr[i] - i - 1 <= 2:
      c += arr[i] - i - 1
      x = applyState(x, arr[i]-1, arr[i] - i - 1)
    elif arr[i] - i - 1 > 2:
      return -1


  for i in xrange(n):
    if arr[i] != x[i]: c += getMore(arr, i)
  return c



T = int(sys.stdin.readline())
for _ in xrange(T):
  n = int(sys.stdin.readline())
  arr = map(int, sys.stdin.readline().strip().split())
  c = solve(n, arr)
  if c == -1:
    print 'Too chaotic'
  else:
    print c