import random
import numpy as np
t = 10000
print(t)
n = 100
q = 350
ns = [i for i in range(1, 500)]
for _ in range(t):
    print(n)
    x = np.random.choice(ns, n)
    print(' '.join([str(i) for i in x]))
    print(q)
    for j in range(1, q+1):
        print(j)

