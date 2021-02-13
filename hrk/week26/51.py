def solve(container):
    n = len(container)
    m = len(container[0])
    row = [0 for i in range(n)]
    col = [0 for j in range(m)]
    x = [[0 for j in range(m)] for i in range(n)]

    for i in range(n):
        c = 0
        for j in range(m):
            c += container[i][j]
        row[i] = c
    for j in range(m):
        c = 0
        for i in range(n):
            c += container[i][j]
        col[j] = c

    for i in range(n):
        for j in range(m):
            if row[i]-container[i][j] == col[j]-container[i][j]:
                x[i][j] = 1
            else:
                x[i][j] = 0

    # for i in range(n):
    #     print(x[i])
    for i in range(n):
        c = 0
        for j in range(m):
            c = c|x[i][j]
        if c == 0:
            return 'Impossible'
    return 'Possible'

q = [
    [2,3,4],
    [3,2,3],
    [4,4,2]
]
print(solve(q))


            
