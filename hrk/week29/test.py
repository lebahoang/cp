import random

n = 2*10**5

arr = []
for _ in xrange(n):
  arr.append(str(random.randint(10000, 99999)))
print n
print '\n'.join(arr)

