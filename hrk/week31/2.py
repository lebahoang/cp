import sys

q = int(sys.stdin.readline())
for _ in xrange(q):
  n = int(sys.stdin.readline())
  arr = map(int, sys.stdin.readline().strip().split(' '))
  rs = 'Yes'
  for i in xrange(n):
    if abs(arr[i] - i) > 1:
      rs = 'No'
      break
  print rs