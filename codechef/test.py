import random
# r = random.randint(1, 100)
# c = random.randint(1, 100)
r = 100
c = 100
# k = random.randint(1, 5)
# l = random.randint(1, 100000)
k = 5
l = 100000
x0 = random.randint(0, r-1)
y0 = random.randint(0, c-1)
print(r, c, k, l)
print(x0, y0)
for _ in range(r):
    t = []
    for _ in range(c):
        t.append(str(random.randint(1, l)))
    print(' '.join(t))