import sys
import math
import random
from fractions import gcd

def isPrime(n):
  if n <= 1:
    return False
  if n == 2:
    return True
  stop = int(n**0.5 + 1.0)
  for i in xrange(2, stop+1):
    if n%i == 0:
      return False
  return True

def generateAllNumber(primes,x,num,rs, first, last):
  if x == 0:
    if len(num) == 1 or (num[-1] != '2' and num[-1] != '5'):
      rs.append(int(num))
    return rs
  for i in primes:
    t = num+str(i)
    if t >= first[:len(t)] and t <= last[:len(t)]: 
      rs = generateAllNumber(primes, x-1, t, rs, first, last)
  return rs

def getAllMegaPrime():
  d = [-1]*12
  primes = [2,3,5,7]
  for i in xrange(1, 12):
    s = '1' + '0'*(i-1)
    e = '9'*i
    t = []
    t = generateAllNumber(primes, i, '', t, s, e)
    c = 0
    for k in t:
      if isPrime(k):
        c += 1
    d[i] = c

  return d

def pollardRho(N):
  if N%2==0:
    return 2
  x = random.randint(1, N-1)
  y = x
  c = random.randint(1, N-1)
  g = 1
  while g==1:             
    x = ((x*x)%N+c)%N
    y = ((y*y)%N+c)%N
    y = ((y*y)%N+c)%N
    g = gcd(abs(x-y),N)
  return g

#print getAllMegaPrime()
#print pollardRho(2222222773)
#print isPrime(2222222773)

### --------------------------- ###
d = [-1, 4, 4, 15, 38, 128, 389, 1325, 4643, 16623, 59241, 214432]
c = 0
first, last = sys.stdin.readline().strip().split()
for i in xrange(len(first), len(last)+1):
  t = []
  primes = [2,3,5,7]
  s = ''
  e = ''
  if i == len(first):
    s = first
  else:
    s = '1' + '0'*(i-1)
  if i == len(last):
    e = last
  else:
    e = '9'*i
  if s <= '2'*(i) and e >= '7'*i: 
    c += d[i]
  else:
    t = generateAllNumber(primes, i, '', t, s, e)
    for k in t:
      if pollardRho(k) == 1:
        c += 1

print c