import math

def check(a, k):
    total = 0
    cur = 1
    while True:
        if total == a:
            return True
        elif total > a:
            break
        else:
            total += cur
            cur = cur*k
    return False
def solve(s):
    a = int(s)
    maxV = 1000
    for k in range(2, maxV):
        if check(a, k):
            return str(k)    
    k = math.floor(a**0.5)
    if check(a, k):
        return str(k)
    return str(a-1)

print(solve('999999999999999999'))