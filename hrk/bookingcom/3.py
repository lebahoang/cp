import sys

kk = []
arr = map(int, sys.stdin.readline().strip().split())

maxC = -1
maxI = -1
for i in xrange(len(arr)):
  x = []
  c = 0
  while c < len(arr):
    x.append(arr[i])
    i += 1
    if  i == len(arr): i = 0
    c += 1

  count = 0
  for j,k in enumerate(x):
    if k <= j:
      count += 1
  if maxC == -1 or maxC < count:
    maxC = count
    maxI = i

  kk.append(x)

print maxC, maxI, arr[maxI]
for x in kk:
  print x
