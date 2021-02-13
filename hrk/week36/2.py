import sys


n = int(sys.stdin.readline())
doors = map(int, sys.stdin.readline().strip().split(" "))


total = 0
minV = 0
c = 0
for d in doors:
    if d == 1:
        total += 1
        c += 1
    else:
        if c%2 == 0:
            minV += c/2
        else:
            minV += c/2+1
        c = 0
if c > 0:
    if c%2 == 0:
        minV += c/2
    else:
        minV += c/2+1
print minV, total