import random
n = 1000
print(n)
for _ in range(n):
    a = random.randint(2, 100000)
    b = random.randint(1, 1000000000)
    print(a,b)
    arr = []
    for _ in range(a):
        arr.append(str(random.randint(1, 1000000000)))
    print(' '.join(arr))
