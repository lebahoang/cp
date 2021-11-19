import sys

def is_invited(i, node, isFriendOf2):
    if isFriendOf2[i] == 1: return False
    for x in node[i]:
        if x != 1 and isFriendOf2[x] == 1: return False
    return True
def solve(n, node, isFriendOf2):
    print(node, isFriendOf2)
    fof1 = []
    for i in node[1]:
        if i != 2:
            fof1.append(i)
    rs = []
    for i in fof1:
        if is_invited(i, node, isFriendOf2):
            rs.append(i)
    if not rs: return '-1'
    rs = sorted(rs)
    rs_map = {}
    for i in rs:
        if i not in rs_map:
            rs_map[i] = 1
    return ' '.join([str(i) for i in rs_map.keys()])


t = int(sys.stdin.readline())
for _ in range(t):
    n, m = map(int, sys.stdin.readline().strip().split(' '))
    isFriendOf2 = [0 for _ in range(n+1)]
    node = [[] for _ in range(n+1)]
    for j in range(m):
        a, b = map(int, sys.stdin.readline().strip().split(' '))
        if a == b: continue
        node[a].append(b)
        node[b].append(a)
        if a == 2: isFriendOf2[b] = 1
        if b == 2: isFriendOf2[a] = 1
    print(solve(n, node, isFriendOf2))

