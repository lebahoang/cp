import sys
def get_x(t, n):
    if (n-t**2)%t == 0:
        return max(0, (n-t**2)//t)
    return max(0, (n-t**2)//t + 1)


n,m = map(int, sys.stdin.readline().strip().split(' '))

arr = [True for _ in range(2,10**6+1)]
arr2 = [True for _ in range(n,m+1)]
if n == 1: arr2[0] = False

t = 2
while True:
    for x in range(t**2, 10**6+1, t):
        arr[x-2] = False
    # now iterate for range (n,m) too
    x = get_x(t, n)
    for xx in range(t**2+t*x, m+1, t):
        # print('xx', xx)
        arr2[xx-n] = False

    tt = t+1
    while tt <= 10**6 and not arr[tt-2]:
        tt += 1
    t = tt
    if t > 10**6:
        break


c = 0
for x in range(n,m+1):
    if x+2 <= m and arr2[x-n] and arr2[x+2-n]:
            # print(x, x+2)
            c += 1
print(c)

