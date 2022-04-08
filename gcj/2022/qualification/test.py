import random

t = 100
print(t)
for _ in range(t):
    d = []
    n = random.randint(100, 1000)
    for i in range(n):
        d.append(random.randint(4, 1000000))
    print(n)
    print(" ".join([str(i) for i in d]))