import random

# t = 1
# print(t)
# for cs in range(t):
#     n = 5
#     m = 5
#     k = random.randint(0, 47)
#     print(n,m,k)
#     arr = [[-1 for _ in range(m)] for _ in range(n)]
#     for i in range(n):
#         for j in range(m):
#             a = 0
#             if i-1 >= 0:
#                 a = arr[i-1][j]
#             b = 0
#             if j-1 >= 0:
#                 b = arr[i][j-1]
#             # arr[i][j] = random.randint(max(a,b), 10**9)
#             arr[i][j] = max(a,b) + random.randint(5,10)
#     for t in arr:
#         print(' '.join([str(x) for x in t]))
t = 100
print(t)
for _ in range(t):
    n = 4
    m = 6
    k = 1
    print(n,m,k)
    arr = []
    for _ in range(n):
        arr.append(str(random.randint(-100, 100)))
    print(' '.join(arr))
    dd = {}
    for _ in range(m):
        while True:
            u = random.randint(1, n)
            v = random.randint(u, n)
            if (u,v) not in dd:
                d = random.randint(-100, 100)
                dd[u,v] = 1
                print(u,v,d)
                break
