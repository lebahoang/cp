import sys
import math


def getDiff(x):
  k = round(math.log(x,2))
  if 2**k >= x:
    k -= 1
  return int(2**k)

n,m = map(int, sys.stdin.readline().strip().split(' '))
one = map(int, sys.stdin.readline().strip().split(' '))

two = []
for i in xrange(n):
  if i < n-1:
    t = one[i] ^ one [i+1]
  else:
    t = one[i] ^ one[0]
  two.append(t)

#print one, two
a = m
needs = [a]
while a != 1 and a != 2:
  diff = getDiff(a)
  a = a - diff
  if a != 1 and a != 2:
    needs.append(a)

needs.reverse()
# print needs,a
if a == 1:
  s = one
else:
  s = two
b = a
for k in needs:
  if k == 1 or k == 2: continue
  t = []
  for i in xrange(n):
    j = (i + k - b)%n
    x = s[i] ^ s[j]
    t.append(x)
  # print t, k, b
  b = k
  s = t[:]


s = [str(i) for i in s]
print ' '.join(s)
