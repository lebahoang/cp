import random
n = 1000
d = {}
for i in range(random.randint(n, 100000)):
    a = random.randint(0, n-1)
    b = random.randint(0, n-1)
    if (a,b) not in d:
        d[a,b] = 1
        print(a)

