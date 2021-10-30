import sys
import math
def computeC (c, n):
  if n < 2: return c,1
  if n == 2: return c,2
  if n > len(c): return c,c[n]
  j = n-1
  x = [j]
  while c[j] == -1:
    x.append(j)
    j -= 1 
  for k in x:
    c.append(c[-1]*k)
  return c,c[n]
def countPair (prod, x,y):
  d = {}
  c = []
  for i in xrange(1, int(math.sqrt(x))+1):
    if x%i == 0 :
      if i != x/i:
        c.append(i)
        c.append(x/i)
        d[i] = 1
        d[x/i] = 1
      else:
        c.append(i)
        d[i] = 1
  cc = []
  repeat = 0
  for i in xrange(1, int(math.sqrt(y))+1):
    if y%i == 0 :
      if i != y/i:
        cc.append(i)
        cc.append(y/i)
        if i in d:
          repeat += 1
        if y/i in d:
          repeat += 1
      else:
        cc.append(i)
        if i in d:
          repeat += 1

  print c,x,cc,y
  if repeat > 1:
    prod, one = computeC(prod,repeat)
    prod, two = computeC(prod,2)
    prod, three = computeC(prod,repeat-2)
    #print repeat, one, two, three
    return prod, len(c)*len(cc) - ( one/(two*three) + repeat )
  return prod, len(c)*len(cc) - repeat

n = int(sys.stdin.readline())

k = []
for i in xrange(1,n/2 + 1):
  j = n-i
  k.append((i,j))

c = [1,1,2,6]
rs = 0
for x,y in k:
  c, count = countPair(c,x,y)
  print 'dddd', count
  rs += count
print rs

