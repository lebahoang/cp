from pickle import BINBYTES
import random

T = 100
print(T)
for _ in range(T):
    n = random.randint(2, 10)
    b = random.randint(1, 100)
    h = []
    d = []
    for _ in range(n):
        h.append(random.randint(1, 100))
        d.append(random.randint(1, 100))
    print(n)
    print(' '.join(str(x) for x in h))
    print(' '.join(str(x) for x in d))
    print(b)