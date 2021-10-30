import sys
s = sys.stdin.readline().strip()
hasOne = False
t = -1
maxV = 0
x = -1
y = -1
for i in range(len(s)):
    if s[i] == '0':
        if x == -1: x = i
        y = i
    else:
        hasOne = True
        if x > -1:
            if x == 0:
                t = y-x+1
                if s[len(s)-1] == '1':
                    maxV = max(maxV, t)
            else:
                maxV = max(maxV, y-x+1)
                if y == len(s)-1:
                    if t > -1:
                        maxV = max(maxV, y-x+1+t)
        x = -1
        y = -1

if x > -1:
    if x == 0:
        t = y-x+1
        if s[len(s)-1] == '1':
            maxV = max(maxV, t)
    else:
        maxV = max(maxV, y-x+1)
        if y == len(s)-1:
            if t > -1:
                maxV = max(maxV, y-x+1+t)
if not hasOne:
    print(-1)
else:
    print(maxV)