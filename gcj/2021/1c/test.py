import random
t = 1000
print(t)
for _ in range(t):
    n = random.randint(1, 30)
    k = random.randint(1, 1000000000)
    x = []
    for _ in range(n):
        x.append(random.randint(1, k))
    print(n,k)
    print(' '.join([str(i) for i in x]))