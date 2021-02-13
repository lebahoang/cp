import sys

def solve1():
  n = int(sys.stdin.readline())
  s = [0]
  while len(s) <= 1000:
    t = [1-i for i in s]
    s.extend(t)

  for _ in range(n):
    q = int(sys.stdin.readline())
    print(s[q])

def printTest():
  import random
  n = 100000
  hit = 100000000
  t = 1000

  #arr = [str(random.randint(1, 1000000000)) for _ in range(n)]
  arr = [str(1000000000) for _ in range(n)]
  print(n,hit,t)
  print(' '.join(arr))

def solve2():
  n,hit,t = map(int, sys.stdin.readline().strip().split())
  arr = map(int, sys.stdin.readline().strip().split())
  arr = sorted(arr)
  c = 0
  start = -1
  for i in range(n):
    if arr[i] <= hit:
      c += 1
    else:
      if start == -1:
        start = i
  if c >= t:
    return min(c,t)
  else:
    t = t - c
    rs = c
    i = start
    while i >= 0 and i < n:
      x = 0
      if arr[i]%hit == 0:
        x = arr[i]/hit
      else:
        x = int(arr[i]/hit) + 1
      if x <= t:
        #print(i, arr[i], t, x)
        t = t - x
        rs += 1
      else:
        break
      i += 1 
    return rs

def solve21():
  n,hit,t = map(int, sys.stdin.readline().strip().split())
  arr = map(int, sys.stdin.readline().strip().split())
  arr = sorted(arr)
  rs = 0
  for i in arr:
    if i <= hit:
      rs += 1
      if t > 0:
        t -= 1
      else:
        break
    else:
      x = 0
      if i%hit == 0:
        x = i/hit
      else:
        x = int(i/hit) + 1
      if x <= t:
        t = t - x
        rs += 1
      else:
        break
  return rs


def getStart1(distance, left, right, s):
  if left > right:
    return None

  mid = int((left+right)/2)
  a = s-mid+1
  if a < 0: a += len(distance)
  if a > len(distance)-1: a -= len(distance)
  b = s-mid
  if b < 0: b += len(distance)
  if b > len(distance)-1: b -= len(distance)
  if distance[a] is not None and distance[b] is None:
    return mid
  if distance[b] is not None:
    return getStart1(distance, mid+1, right, s)
  return getStart1(distance, left, mid-1, s)

def getStart2(distance, left, right, s):
  if left > right:
    return None

  mid = int((left+right)/2)
  a = s+mid-1
  if a < 0: a += len(distance)
  if a > len(distance)-1: a -= len(distance)
  b = s+mid
  if b < 0: b += len(distance)
  if b > len(distance)-1: b -= len(distance)
  if distance[a] is not None and distance[b] is None:
    return mid
  if distance[b] is not None:
    return getStart2(distance, mid+1, right, s)
  return getStart2(distance, left, mid-1, s)


import sys
import time
import queue

def modexp ( g, u, p ):
   """computes s = (g ^ u) mod p
      args are base, exponent, modulus
      (see Bruce Schneier's book, _Applied Cryptography_ p. 244)"""
   s = 1
   while u != 0:
      if u & 1:
         s = (s * g)%p
      u >>= 1
      g = (g * g)%p;
   return s

def getInd(point, n):
  x = -1
  if point < 0:
    x = abs(point)
    #tt, mod = divmod(x, n)
    mod = x%n
    x = int(point + n*((x - mod )/n + 1))
  else:
    x = point
  #return divmod(x,n)[1]
  return x%n

#q = queue.Queue()
a = []

for _ in range(1, 10000000):
  getInd(10000000, 34)
  a.append(3)
print('ok')


