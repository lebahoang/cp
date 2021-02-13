def find_all_components(grid):
    n = len(grid)
    m = len(grid[0])
    zeros = 0
    components = []
    checked = [[0 for j in range(m)] for i in range(n)]
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 0: 
                zeros += 1
                continue
            elif grid[i][j] == 2:
                continue
            if checked[i][j] == 1:
                continue
            component = []
            stack = [(i,j)]
            checked[i][j] = 1
            while stack:
                ii, jj = stack.pop(-1)
                component.append((ii, jj))
                if ii-1 >= 0 and grid[ii-1][jj] == 1 and checked[ii-1][jj] == 0:
                    stack.append((ii-1, jj))
                    checked[ii-1][jj] = 1
                if ii+1 < n and grid[ii+1][jj] == 1 and checked[ii+1][jj] == 0:
                    stack.append((ii+1, jj))
                    checked[ii+1][jj] = 1
                if jj-1 >= 0 and grid[ii][jj-1] == 1 and checked[ii][jj-1] == 0:
                    stack.append((ii, jj-1))
                    checked[ii][jj-1] = 1
                if jj+1 < m and grid[ii][jj+1] == 1 and checked[ii][jj+1] == 0:
                    stack.append((ii, jj+1))
                    checked[ii][jj+1] = 1
            components.append(component)
    return components, zeros

def count_effected_area_of_component(grid, component):
    n = len(grid)
    m = len(grid[0])
    checked = [[0 for j in range(m)] for i in range(n)]
    c = 0
    for cell in component:
        i,j = cell
        if i-1 >= 0 and grid[i-1][j] == 0 and checked[i-1][j] == 0:
            c += 1
            checked[i-1][j] = 1
        if i+1 < n and grid[i+1][j] == 0 and checked[i+1][j] == 0:
            c += 1
            checked[i+1][j] = 1
        if j-1 >= 0 and grid[i][j-1] == 0 and checked[i][j-1] == 0:
            c += 1
            checked[i][j-1] = 1
        if j+1 < m and grid[i][j+1] == 0 and checked[i][j+1] == 0:
            c += 1
            checked[i][j+1] = 1
    return c


def count_used_walls(grid, blocked_component):
    n = len(grid)
    m = len(grid[0])
    used = 0
    for cell in blocked_component[0]:
        i,j = cell
        if i-1 >= 0 and grid[i-1][j] == 0:
            used += 1
        if i+1 < n and grid[i+1][j] == 0:
            used += 1
        if j-1 >= 0 and grid[i][j-1] == 0:
            used += 1
        if j+1 < m and grid[i][j+1] == 0:
            used += 1
    return used

def rank_components(grid, components):
    m = -1
    c = None
    cs = []
    for component in components:
        rank = count_effected_area_of_component(grid, component)
        cs.append((component, rank))
        if rank > m:
            m = rank
            c = cs[-1]

    return c, cs

def simulate_effected_component(grid, component):
    n = len(grid)
    m = len(grid[0])
    for cell in component:
        i,j = cell
        if i-1 >= 0 and grid[i-1][j] == 0:
            grid[i-1][j] = 1
        if i+1 < n and grid[i+1][j] == 0:
            grid[i+1][j] = 1
        if j-1 >= 0 and grid[i][j-1] == 0:
            grid[i][j-1] = 1
        if j+1 < m and grid[i][j+1] == 0:
            grid[i][j+1] = 1

def run_a_night(grid, blocked_component, components):
    # block blocked_component
    for cell in blocked_component[0]:
        i,j = cell
        grid[i][j] = 2
    # simulate effected area
    for component, rank in components:
        if rank != blocked_component[1]:
            simulate_effected_component(grid, component)

def solve(grid):
    def print_all(grid):
        for i in range(len(grid)):
            print(grid[i])

    c = 0
    walls = 0
    while True:
        components, zeros = find_all_components(grid)
        if not components: 
            break
        if zeros == 0:
            return walls
        blocked_component, components = rank_components(grid, components)
        # print_all(grid)
        # print(components)
        # print('-------------')
        walls += count_used_walls(grid, blocked_component)
        run_a_night(grid, blocked_component, components)
    return walls


# grid = [
#  [0,1,0,0,0,0,0,1],
#  [0,1,0,0,0,0,0,1],
#  [0,0,0,0,0,0,0,1],
#  [0,0,0,0,0,0,0,0]
# ]

# grid = [[1,1,1],
#  [1,0,1],
#  [1,1,1]]


# grid = [
#  [1,1,1,0,0,0,0,0,0],
#  [1,0,1,0,1,1,1,1,1],
#  [1,1,1,0,0,0,0,0,0]]

grid = [
    [1,1,1],
    [1,1,0],
    [1,1,1]
]


# grid = [
#     [0,1,0,1,1,1,1,1,1,0],
#     [0,0,0,1,0,0,0,0,0,0],
#     [0,0,1,1,1,0,0,0,1,0],
#     [0,0,0,1,1,0,0,1,1,0],
#     [0,1,0,0,1,0,1,1,0,1],
#     [0,0,0,1,0,1,0,1,1,1],
#     [0,1,0,0,1,0,0,1,1,0],
#     [0,1,0,1,0,0,0,1,1,0],
#     [0,1,1,0,0,1,1,0,0,1],
#     [1,0,1,1,0,1,0,1,0,1]]
print(solve(grid))