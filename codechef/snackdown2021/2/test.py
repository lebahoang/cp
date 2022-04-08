import random
t = 10
print(t)
for _ in range(t):
    n = 5
    print(n)
    arr = []
    for _ in range(n):
        arr.append(random.randint(1, 5))
    arr = sorted(arr)
    print(' '.join([str(x) for x in arr]))
