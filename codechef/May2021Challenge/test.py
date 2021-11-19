import math


for add in range(3, 100, 2):
    maxV = -1
    d = {}
    for a in range(1, 3000001):
        t = math.gcd(a, a+add)
        d[t] = 1
        maxV = max(maxV, t)
    print(add, maxV, list(d.keys()))