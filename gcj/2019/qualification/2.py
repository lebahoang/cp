import sys


def solve(visited_path, n, i, j, rs):
    if len(rs) > 2*n-2:
        return []
    if i == n or j == n:
        return []
    if i == n-1 and j == n-1:
        if len(rs) == 2*n-2:
            return rs[:]
        return []

    if (i, j, i+1, j) not in visited_path:
        rs.append('S')
        final = solve(visited_path, n, i+1, j, rs)
        if len(final) > 0:
            return final
        rs = rs[:-1]
    if (i, j, i, j+1) not in visited_path:
        rs.append('E')
        final = solve(visited_path, n, i, j+1, rs)
        if len(final) > 0:
            return final
        rs = rs[:-1]
    return []

def solve2(visited_path):
    rs = []
    for d in visited_path:
        if d == 'S':
            rs.append('E')
        else:
            rs.append('S')
    return ''.join(rs)

def sample(n, i, j, rs):
    if i == n or j == n:
        return []
    if i == n-1 and j == n-1:
        if len(rs) == 2*n-2:
            return rs[:]
        return []
    
    rs.append('S')
    final = sample(n, i+1, j, rs)
    if len(final) > 0:
        return final
    rs = rs[:-1]
    
    rs.append('E')
    final = sample(n, i, j+1, rs)
    if len(final) > 0:
        return final
    rs = rs[:-1]

    return []


testset = int(sys.stdin.readline())
for case in range(testset):
    n = int(sys.stdin.readline())
    visited_path = sys.stdin.readline().strip()
    # visited = {}
    # i = 0
    # j = 0
    # for d in visited_path:
    #     if d == 'S':
    #         visited[(i, j, i+1, j)] = 1
    #         i += 1
    #     else:
    #         visited[(i, j, i, j+1)] = 1
    #         j += 1
    # p = solve(visited, n, 0, 0, [])
    p = solve2(visited_path)
    print('Case #{:d}: {}'.format(case+1, ''.join(p)))


# p = sample(1000, 0, 0, [])
# print(''.join(p))
