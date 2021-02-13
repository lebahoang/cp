import sys


n = int(sys.stdin.readline())
for case in range(n):
    t = int(sys.stdin.readline())
    t = str(t)
    a = []
    b = []
    for j in t:
        j = int(j)
        if j == 0:
            a.append(0)
            b.append(0)
        else:
            if j-1 == 4:
                a.append(2)
                b.append(j-2)
            else:
                a.append(1)
                b.append(j-1)
    rsa = ''.join([str(i) for i in a])
    rsb = ''.join([str(i) for i in b])
    print('Case #{:d}: {} {}'.format(case+1, rsa, rsb))
