import random


case = 10
print(case)
for _ in range(case):
    # n = random.randint(5, 10)
    n = 10
    arr = []
    for _ in range(n):
        arr.append(random.randint(1, 3))
    print(n)
    print(' '.join([str(x) for x in arr]))