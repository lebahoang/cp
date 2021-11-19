import sys

n = int(sys.stdin.readline())
a = map(int, sys.stdin.readline().strip().split(' '))
m,hmin,hmax = map(int, sys.stdin.readline().strip().split(' '))

b = [hmax]
for i in xrange(n-1):
  b.append(a[i+1] - a[i])
b.append(hmax)

d = [[0,None] for i in xrange(n+1)]

for i in xrange(n+1):
  if i == 0:
    t = 0
    j = 1
  else:
    if d[i-1][0] != None:
      t = d[i-1][0] - b[i-1]
      j = d[i-1][1] + 1
    else:
      if (b[i-1] < hmin or b[i-1] > hmax) and (b[i] >= hmin and b[i] <= hmax):
        t = 0
        j = i+1
      else:
        t = None
        j = None

  f = 0
  if t != None:
    while t < m and j <= n+1:
      if b[j-1] < hmin or b[j-1] > hmax:
        f = 1
        break
      t += b[j-1]
      j += 1
    if j > n+1 and t < m:
      f = 1
  else:
    f = 1
  if f == 0:
    d[i] = [t, j-1]
  else:
    d[i] = [None, None]

print d
pos = None
for i in xrange(n+1):
  if d[i][0] != None:
    if d[i][0] == m:
      ii = i-1
      if ii >= 0:
        pos = a[ii]
      elif ii < 0:
        pos = a[ii+1]-hmax
      # break
    else:
      ii = i-1
      iii = d[i][1]-1
      remove = d[i][0]-m

      # print ii,iii,b
      f = 0
      if ii < 0:
        k = hmax-remove
      else:
        k = b[i] - (a[ii]+remove)
      if k >= hmin and k <= hmax:
        if ii < 0:
          pos = a[0]-hmax+remove
        else:
          pos = a[ii]+remove
        f = 1
      #if f == 1: break
      if iii < n:
        l = b[iii] - (a[iii]-remove)
      else:
        l = hmax-remove
      if l >= hmin and l <= hmax:
        if ii < 0:
          pos = a[0]-hmax+remove
        else:
          pos = a[ii]
        f = 1
      #if f == 1: break
print pos






