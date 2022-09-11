import random

T = 100
print(T)
for i in range(T):
    N = random.randint(1000, 2006)
    print(N)
    for _ in range(N):
        x = random.randint(1000000000, 1000000000)
        y = random.randint(1000000000, 1000000000)
        print(x, y)
    Q = random.randint(3000, 5006)
    print(Q)
    for _ in range(Q):
        x = random.randint(10000000, 1000000000)
        y = random.randint(10000000, 1000000000)
        print(x, y)