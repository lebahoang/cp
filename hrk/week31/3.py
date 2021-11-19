import sys

def count(arr, n):
  c = 0
  h = {}
  for i in xrange(1, len(arr)-1):
    if arr[i-1] == 0 and arr[i+1] == 0:
      if arr[i] == 1:
        if i-1 > 0 and i-1 not in h:
          h[i-1] = 1
        if i+1 < n-1 and i+1 not in h:
          h[i+1] = 1
      c += 1
  

  for k in h.keys():
    s = k-2 if k-2 >= 0 else 0
    j = k-1
    b = 0
    while j >= s:
      if arr[j] == 1:
        b += 1
      j -= 1

    if b >= 2 or (b > 0 and k-2 < 0):
      continue

    s = k+2 if k+2 < n else n-1
    j = k+1
    b = 0
    while j <= s:
      if arr[j] == 1:
        b += 1
      j += 1

    if b >= 2 or (b > 0 and k+2 > n-1):
      continue

    c += 1
  #print h,c
  return c
n = int(sys.stdin.readline())
for _ in xrange(n):
  num = int(sys.stdin.readline())
  arr = map(int, sys.stdin.readline().strip().split())
  numOf2 = count(arr,num)
  if numOf2 % 2 == 0:
    print 'Bob'
  else:
    print 'Alice'