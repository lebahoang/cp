import itertools
import sys

n = int(sys.stdin.readline())
x = list(map(int, sys.stdin.readline().strip().split(' ')))
y = list(map(int, sys.stdin.readline().strip().split(' ')))
ps = list(itertools.permutations([i for i in range(1, n+1)]))
ps = sorted(ps)
# print(ps)

a = 0
b = 0

for ind, p in enumerate(ps):
    f1 = True
    for i,j in zip(p,x):
        if i != j:
            f1 = False
            break
    if f1:
        a = ind+1

    f2 = True
    for i,j in zip(p,y):
        if i != j:
            f2 = False
            break

    if f2:
        b = ind+1
# print(a, b)
print(abs(a-b))

