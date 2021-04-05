import random

t = 1
for i in range(t):
    print(i+1)
    n = 1000
    m = 1000
    k = random.randint(0, 10**9)
    print(n,m,k)
    for _ in range(n):
        t = []
        for _ in range(m):
            t.append(str(random.randint(0, 10**9)))
        print(' '.join(t))

