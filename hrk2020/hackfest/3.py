import sys
n,q = map(int, sys.stdin.readline().strip().split(' '))
ns = []
for _ in range(n):
    r,b,g = map(int, sys.stdin.readline().strip().split(' '))
    ns.append((r,b,g))

mq = {}
qs = []
ans = []
for i in range(q):
    r,b,g = map(int, sys.stdin.readline().strip().split(' '))
    if r not in mq: mq[r] = [i]
    else: mq[r].append(i)
    qs.append((r,b,g))
    ans.append('NO')
ns = sorted(ns)
mb = {}
for r,b,g in ns:
    if b not in mb:
        mb[b] = []
    mb[b].append(g)
    t = []
    if r not in mq: continue
    for i in mq[r]:
        qb, qg = qs[i][1], qs[i][2]
        if qb >= b and qb in mb and qg >= g:
            for gg in mb[b]:
                if qg >= gg:
                    ans[i] = 'YES'
        else:
            t.append(i)
    mq[r] = t[:]

for s in ans:
    print(s)