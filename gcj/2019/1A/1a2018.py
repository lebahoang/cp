import sys
def cut(arr, x):
    rs = []
    t = 0
    for i in range(len(arr)):
        t += arr[i]
        if t == x:
            rs.append(i)
            t = 0
    return rs

def solve(r,c,h,v,arr):
    chips = 0
    for i in range(r):
        for j in arr[i]:
            if j == '@': chips += 1
    if chips == 0: return 'POSSIBLE'
    if chips%((h+1)*(v+1)) != 0:
        return 'IMPOSSIBLE'
    x = chips//(h+1)
    a = []
    for i in range(r):
        m = 0
        for j in arr[i]:
            if j == '@':
                m += 1
        a.append(m)
    rs1 = cut(a, x)
    if len(rs1) != h+1:
        return 'IMPOSSIBLE'
    rs1 = [-1] + rs1 + [r-1]
    x = chips//(v+1)
    a = []
    for j in range(c):
        m = 0
        for i in range(r):
            if arr[i][j] == '@':
                m += 1
        a.append(m)
    rs2 = cut(a, x)
    if len(rs2) != v+1:
        return 'IMPOSSIBLE'
    rs2 = [-1] + rs2 + [c-1]

    print(rs1, rs2)
    x = chips//((h+1)*(v+1))
    for i in range(len(rs1)-1):
        for j in range(len(rs2)-1):
            if rs1[i] >= rs1[i+1] or rs2[j] >= rs2[j+1]: continue
            section_chips = 0
            for k in range(rs1[i]+1, rs1[i+1]+1):
                for l in range(rs2[j]+1, rs2[j+1]+1):
                    if arr[k][l] == '@': section_chips += 1
            # print('kkk', rs1[i]+1, rs1[i+1]+1, rs2[j]+1, rs2[j+1]+1 ,section_chips)
            if section_chips != x: return 'IMPOSSIBLE'
    return 'POSSIBLE'




t = int(sys.stdin.readline())
for case in range(t):
    r,c,h,v = map(int, sys.stdin.readline().strip().split(' '))
    arr = []
    for _ in range(r):
        line = sys.stdin.readline().strip()
        arr.append(line)
    rs = solve(r,c,h,v,arr)
    print('Case #{:d}: {}'.format(case+1, rs))