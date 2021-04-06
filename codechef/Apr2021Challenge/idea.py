import random

t = 1
print(t)
for cs in range(t):
    n = 5
    m = 5
    k = random.randint(0, 47)
    print(n,m,k)
    arr = [[-1 for _ in range(m)] for _ in range(n)]
    for i in range(n):
        for j in range(m):
            a = 0
            if i-1 >= 0:
                a = arr[i-1][j]
            b = 0
            if j-1 >= 0:
                b = arr[i][j-1]
            # arr[i][j] = random.randint(max(a,b), 10**9)
            arr[i][j] = max(a,b) + random.randint(5,10)
    for t in arr:
        print(' '.join([str(x) for x in t]))
