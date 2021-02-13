import random

t = 100
print(t)
n = 10
for i in range(t):
    s = ''
    for j in range(n):
        s += str(random.randint(0,1))
    print(n, random.randint(0, n))
    print(s)