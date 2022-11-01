import random

from numpy import sort
n = 1000000
q = 1000000
print(n, q)
a = random.sample(range(1, n+1), n)
a = sorted(a)
print(' '.join([str(x) for x in a]))
b1 = random.sample(range(-n, 0, 1), 100000)
b2 = random.sample(range(1, n+1), q-100000)
b = sorted(b1+b2)
print(' '.join([str(x) for x in b]))