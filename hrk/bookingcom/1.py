import sys

n = int(sys.stdin.readline())
arr = map(int, sys.stdin.readline().strip().split())

avail = -1
for i in arr:
  if avail == -1 or avail < i:
    avail = i
  elif avail >= i:
    avail += 1
print avail
