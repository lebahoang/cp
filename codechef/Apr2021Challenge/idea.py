import random

n = 10
m = 10
arr = []
for _ in range(20):
    t = []
    for i in range(m):
        if i == 0:
            t.append(random.randint(1, 100))
        else:
            x = t[i-1] + random.randint(1, 10)
            t.append(x)
    arr.append(t)

k = random.randint(1, 100)
for i in range(n):
    for j in range(m):
        arr[i][j] -= k
sum = [[0 for j in range(m)] for i in range(n)]
for i in range(n):
    prefix = 0
    for j in range(m):
        arr[i][j] -= k
        prefix += arr[i][j]
        sum[i][j] += prefix + sum[i-1][j]

for i in range(n):
    print(sum[i])
