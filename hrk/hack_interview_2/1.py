import sys
n, m = map(int, sys.stdin.readline().strip().split(' '))
arr = list(map(int, sys.stdin.readline().strip().split(' ')))
arr = sorted(arr)
mod = 10**9 + 7
ind = 1
i = 0
total = 0
while i < n:
    s = 0
    for j in range(i, i+m):
        s += arr[j]
    if i+m+m > n:
        for j in range(i+m, n):
            s += arr[j]
        i = n
    else:
        i += m
    total += ind*s
    ind += 1
print(total%mod)
