import sys

PI = 3.14159265358979323846264338327950288419716939937510582
n,k = map(int, sys.stdin.readline().strip().split())
arr = map(int, sys.stdin.readline().strip().split())

d = [1]*(n+1)
for i in xrange(1, n+1):
  d[i] = d[i-1]*i


print rs
