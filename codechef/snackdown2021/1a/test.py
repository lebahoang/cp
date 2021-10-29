import random

t = 1000
print(t)
for _ in range(t):
    n = random.randint(2, 10**5)
    n = 10
    print(n)
    a = []
    for i in range(n):
        a.append(str(random.randint(-10**9, 10**9)))
        # a.append(str(random.randint(-100, 100)))
    print(' '.join(a))