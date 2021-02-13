import sys

imp = 'IMPOSSIBLE'
pos = 'POSSIBLE'

def go(start, r, c, visited, path, totals):
    # print(len(path))
    x,y = start
    if len(path) == r*c:
        print('vvvvv')
        totals.append(path[:])
        return
    
    xx = -1
    yy = -1
    k = 2
    while  True:
        if x + k >= min(x+2, r):
            break
        if y+1 < c and (x+k, y+1) not in visited:
            xx = x+k
            yy = y+1
            visited[xx, yy] = 1
            go((xx, yy), r, c, visited, path + [(xx,yy)], totals)
            if len(totals) > 0: return
            del visited[xx, yy]
        if y-1 >= 0 and (x+k, y-1) not in visited:
            xx = x+k
            yy = y-1
            visited[xx, yy] = 1
            go((xx, yy), r, c, visited, path + [(xx,yy)], totals)
            if len(totals) > 0: return
            del visited[xx, yy]
        k += 1

    k = 2
    while True:
        if x-k < max(0, x-2):
            break
        if y+1 < c and (x-k, y+1) not in visited:
            xx = x-k
            yy = y+1
            visited[xx, yy] = 1
            go((xx, yy), r, c, visited, path + [(xx,yy)], totals)
            if len(totals) > 0: return
            del visited[xx, yy]
        if y-1 >= 0 and (x-k, y-1) not in visited:
            xx = x-k
            yy = y-1
            visited[xx, yy] = 1
            go((xx, yy), r, c, visited, path + [(xx,yy)], totals)
            if len(totals) > 0: return
            del visited[xx, yy]
        k += 1

    k = 2
    while True:
        if y+k >= min(c, y+2):
            break
        if x+1 < r and (x+1, y+k) not in visited:
            xx = x+1
            yy = y+k
            visited[xx, yy] = 1
            go((xx, yy), r, c, visited, path + [(xx,yy)], totals)
            if len(totals) > 0: return
            del visited[xx, yy]
        if x-1 >= 0 and (x-1, y+k) not in visited:
            xx = x-1
            yy = y+k
            visited[xx, yy] = 1
            go((xx, yy), r, c, visited, path + [(xx,yy)], totals)
            if len(totals) > 0: return
            del visited[xx, yy]
        k += 1

    k = 2
    while True:
        if y-k < max(0, y-2):
            break
        if x+1 < r and (x+1, y-k) not in visited:
            xx = x+1
            yy = y-k
            visited[xx, yy] = 1
            go((xx, yy), r, c, visited, path + [(xx,yy)], totals)
            if len(totals) > 0: return
            del visited[xx, yy]
        if x-1 >= 0 and (x-1, y-k) not in visited:
            xx = x-1
            yy = y-k
            visited[xx, yy] = 1
            go((xx, yy), r, c, visited, path + [(xx,yy)], totals)
            if len(totals) > 0: return
            del visited[xx, yy]
        k += 1
    return

def solve(r,c):
    for i in range(r):
        for j in range(c):
            visited = {(i,j): 1}
            path = [(i,j)]
            totals = []
            go((i,j), r, c, visited, path, totals)
            for path in totals:
                if len(path) == r*c:
                    return True, path
            # print('-----------')
    return False, []



t = int(sys.stdin.readline().strip())
for case in range(t):
    r, c = map(int, sys.stdin.readline().strip().split(' '))
    is_possible, path = solve(r,c)
    if is_possible:
        print('Case #{:d}: {}'.format(case+1, pos))
        for p in path:
            print('{:d} {:d}'.format(p[0]+1, p[1]+1))
    else:
        print('Case #{:d}: {}'.format(case+1, imp))
