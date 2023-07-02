import random
def solution(A):
    b = A
    i = 0
    while True:
        if b[i] <= 1 and i == len(b)-1:
            break
        t = 0
        if b[i]%2 == 0:
            t = b[i]//2
        else:
            t = (b[i]-1)//2
        b[i] = b[i] - 2*t
        if i+1 < len(b):
            b[i+1] += t
        else:
            b.append(t)
        i += 1
    print(b, len(b))
    return sum(b)

a = [0 for _ in range(100000)]
print(solution(a))
# print(solution([1000000]))