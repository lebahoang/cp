# def go(grid):
#     n = len(grid)
#     m = len(grid[0])
#     dp = [[[0, None] for j in range(m)] for i in range(n)]
#     for i in range(n):
#         for j in range(m):
#             if grid[i][j] == -1:
#                 dp[i][j][0] = -1
#                 continue
#             if i == 0 and j == 0:
#                 dp[i][j][0] = grid[i][j]
#                 continue
#             t = -1
#             indt = None
#             if i-1 >= 0 and grid[i-1][j] != -1:
#                 t = dp[i-1][j][0]
#                 indt = (i-1, j)
#             tt = -1
#             indtt = None
#             if j-1 >= 0 and grid[i][j-1] != -1:
#                 tt = dp[i][j-1][0]
#                 indtt = (i,j-1)
#             if t == -1 and tt == -1:
#                 dp[i][j][0] = -1
#                 continue
#             if t > tt:
#                 dp[i][j][0] = t + grid[i][j]
#                 dp[i][j][1] = indt
#             else:
#                 dp[i][j][0] = tt + grid[i][j]
#                 dp[i][j][1] = indtt

#     return dp

# def mark(grid, dp, i, j):
#     it = (i,j)
#     while it is not None:
#         i,j = it
#         grid[i][j] = 0
#         it = dp[i][j][1]
#     return grid
# def solve741(grid):
#     n = len(grid)
#     m = len(grid[0])
#     dp = go(grid)
#     if dp[n-1][m-1][0] == -1:
#         return 0
#     c = dp[n-1][m-1][0]
#     grid = mark(grid, dp, n-1, m-1)
#     dp = go(grid)
#     c += dp[n-1][m-1][0]
#     return c


# def go(grid, dp, i, j, k, p):
#     # if dp[i][j][k][p] != -2:
#     #     return dp[i][j][k][p]
#     if (i,j,k,p) in dp:
#         return dp[i,j,k,p]

#     if grid[i][j] == -1 or grid[k][p] == -1:
#         # dp[i][j][k][p] = -1
#         # return dp[i][j][k][p]
#         dp[i,j,k,p] = -1
#         return dp[i,j,k,p]
        
#     a = b = c = d = -1
#     if i-1 >= 0 and k-1 >= 0:
#         a = go(grid, dp, i-1, j, k-1, p)
#     if i-1 >= 0 and p-1 >= 0:
#         b = go(grid, dp, i-1, j, k, p-1)
#     if j-1 >= 0 and k-1 >= 0:
#         c = go(grid, dp, i, j-1, k-1, p)
#     if j-1 >= 0 and p-1 >= 0:
#         d = go(grid, dp, i, j-1, k, p-1)

#     if a == -1 and b == -1 and c == -1 and d == -1:
#         # dp[i][j][k][p] = -1
#         # return dp[i][j][k][p]
#         dp[i,j,k,p] = -1
#         return dp[i,j,k,p]
#     # dp[i][j][k][p] = max(a,b,c,d) + grid[i][j]
#     dp[i,j,k,p] = max(a,b,c,d) + grid[i][j]
#     if i != k or j != p:
#         dp[i,j,k,p] += grid[k][p]
#     return dp[i,j,k,p]
# def solve741(grid):
#     n = len(grid)
#     m = len(grid[0])

#     dp = {}
#     dp[(0,0,0,0)] = grid[0][0]
#     rs = go(grid, dp, n-1, m-1, n-1, m-1)
#     if rs == -1: return 0
#     return rs






# grid = [
#     [1,-1],
#     [1,0]
# ]
# grid = [
#     [0, 1, -1],
#     [1, 0, -1],
#     [-1, 1,  1]]

# grid = [[0 for _ in range(50)] for _ in range(50)]
# grid = [
#     [1,1,-1],
#     [1,-1,1],
#     [-1,1,1]]
# grid = [[1,0,0,-1,1,1,-1,0,1,-1,0,1,1,0,1,1,-1,0,-1,1,1,0,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,-1,1,1,1,1,-1,1,1],[1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,-1,-1,1,1,-1,1,1,0,0,1,0,-1,1,1],[0,1,1,1,1,1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,1,1,1,-1,-1,1,-1,-1,1,1,1,1,-1,1,0,1,-1,1,1,-1,1,1,1,1,1,1,-1,1,1,1,1,1],[1,1,1,1,1,1,1,1,-1,1,1,1,1,0,1,1,1,1,1,-1,1,-1,1,1,1,1,1,1,1,1,1,1,1,1,0,-1,1,1,1,-1,1,0,1,1,1,1,1,0,1,1],[1,1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,0,-1,1,1,-1,1,1,1,0,-1,0,1,1,0,1,1,1,-1,1,-1,1,1,1,0,1,1,1,0,1,1,0,1,1],[1,1,1,1,1,0,1,-1,-1,-1,0,-1,0,1,1,-1,1,1,1,-1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1],[1,1,1,1,-1,1,-1,1,1,1,1,1,1,-1,1,-1,1,1,0,1,1,1,0,1,1,1,-1,1,1,1,1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1],[1,1,1,1,1,0,1,-1,1,1,1,1,1,1,-1,1,1,1,1,-1,1,1,-1,0,1,1,1,0,1,1,-1,1,1,1,1,1,1,1,1,-1,1,1,1,0,1,1,1,1,1,-1],[1,0,1,1,1,1,1,0,0,1,1,1,1,1,-1,1,1,1,-1,-1,-1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,-1,1,1,0,1,1,1,1,1,-1,1,1,1,1,1],[1,1,1,1,1,0,1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,-1,-1,1,-1,1,1,1,1,1,1,0,1,-1,1,-1,1,-1,-1,1,-1,1,1,1,1,1,1,1,1,1],[1,1,1,-1,1,-1,1,1,-1,1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,1,1,0,-1,1,-1,1,1,-1,1,1,1,-1,0,-1,1,-1,1,-1,1,1,1,1,1,0,1,1],[1,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,-1,1,-1,1,1,1,-1,1,0,1,0,1,1,1,1,-1,1,1,1,-1,1,-1,1,1,1,1,1,1,1],[1,1,1,-1,1,1,1,1,1,-1,1,0,1,-1,1,1,0,1,1,1,-1,-1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,-1,-1,1,1,-1,1,1],[-1,1,1,1,-1,1,1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,1,-1,1,0,1,1,1,1,1,1,-1,1,1,1],[1,1,1,1,1,1,1,0,-1,1,0,1,1,1,1,1,0,1,0,1,1,-1,1,-1,1,0,1,0,1,-1,1,1,0,-1,1,1,1,1,1,1,1,1,-1,1,1,1,0,1,1,-1],[0,1,-1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,-1,0,1,1,-1,1,1,1,1,1,1,1,1,-1,1,1,1,-1,1,1,1,0,0,-1,1,1,1,1,1,1,1,1],[0,-1,1,0,-1,0,-1,1,-1,1,1,0,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,-1,0,1,1,1,1,1,-1,1,1,1,0,1,1,-1,-1,1,1,1,1,1,1],[1,-1,1,1,1,1,1,1,0,1,1,1,0,1,-1,0,-1,1,1,1,-1,0,1,-1,-1,0,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,-1,0,1,1,-1,1,-1,1,-1,1,1,1,1,-1,1,1,1,1,1,1,1,1,-1,0,1,-1,1,1,1,-1,1,1,1,-1,1,1,1,1,0,-1,-1,0,1,1,1,1,-1],[-1,1,1,1,1,1,1,1,-1,1,1,1,0,1,1,1,-1,1,1,0,1,1,1,0,1,0,1,-1,-1,1,1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,0],[1,1,0,-1,1,1,1,1,1,1,1,1,1,1,1,0,-1,-1,0,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,1,1,-1,1,1,1,1,1,1,1,-1,1],[0,1,-1,1,0,-1,1,-1,-1,1,1,1,0,1,-1,-1,0,1,1,1,-1,1,1,-1,1,-1,1,1,1,1,1,1,0,1,-1,1,1,1,1,1,1,1,-1,-1,1,-1,1,1,1,1],[0,1,1,1,1,-1,1,1,-1,-1,1,1,1,1,1,1,1,1,-1,1,1,1,-1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,-1,1],[1,-1,-1,1,-1,-1,1,1,1,1,1,1,1,1,1,1,0,1,1,-1,1,0,-1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,-1,-1,-1,0,-1,1,0,1,-1,1,1,1,1,-1],[1,1,1,1,1,1,1,1,1,-1,1,-1,0,1,0,1,1,-1,-1,1,1,1,1,1,0,1,-1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,-1,1,1,1,0,-1,1,1,1,1],[1,-1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,-1,1,1,1,0,1,1,-1,0,1,1,1,1,1,1,1,-1,1,1,1,0,0,-1,1,-1,-1,1,1,1,-1,1,1,1,1],[1,1,1,1,1,1,-1,1,1,-1,1,1,1,1,-1,0,1,-1,1,0,1,1,1,1,1,1,0,1,1,-1,1,-1,1,1,1,1,1,1,-1,1,1,0,1,-1,1,1,1,-1,1,1],[1,1,1,0,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,1,-1,1,-1,1,1,1,-1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,0,1,1,0,1,1,1,-1,1],[1,1,-1,-1,1,1,1,1,0,-1,1,1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,1,0,0,1,1,0,1,-1,1,1,1,1,1,0,1,1,-1,1],[1,1,1,1,1,-1,1,1,1,1,-1,1,1,-1,1,1,1,0,1,0,1,1,1,1,-1,1,-1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,1,1,1],[0,1,-1,1,1,1,1,-1,0,1,1,1,1,1,1,-1,1,1,1,1,1,1,0,-1,1,1,1,1,0,1,1,1,1,-1,1,-1,1,1,1,-1,1,0,1,1,1,1,1,1,1,1],[1,0,-1,-1,0,1,1,0,-1,1,1,-1,1,1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,1,1,-1,1,-1,1,1,1,1,0,-1,1,0,1,1,1,1,1,-1,-1,1,1,1],[1,1,1,1,1,-1,0,-1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,-1,1,1,1,-1,1,1,1,1,1,1,1,1,1],[1,-1,1,0,1,1,1,1,1,1,-1,1,1,0,1,1,1,1,0,0,1,1,1,-1,1,1,1,0,0,1,-1,1,1,1,0,1,1,1,-1,1,-1,1,1,1,-1,1,1,0,1,-1],[1,1,1,0,-1,1,1,1,1,1,1,1,-1,0,1,1,1,-1,1,0,1,1,-1,1,1,1,-1,0,1,1,-1,1,0,1,0,-1,1,-1,-1,0,1,1,0,1,1,1,1,-1,-1,1],[1,-1,-1,1,-1,-1,0,1,1,-1,1,-1,1,0,1,1,-1,1,1,1,1,1,1,-1,0,1,0,-1,1,1,-1,1,1,1,1,-1,0,1,-1,-1,1,1,1,1,1,1,1,-1,1,-1],[0,1,-1,-1,-1,1,-1,-1,0,1,1,1,1,0,1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,1,1,1,1,1,-1,-1,0,1,1,1,1,1],[1,1,1,1,1,1,1,-1,1,1,1,1,0,1,1,-1,1,1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,1,1,1,1,-1,1,0,-1,1,0,-1,1,1,1,1,1,1,-1,1,1],[1,-1,1,1,1,0,0,0,1,0,1,1,1,1,1,-1,1,1,0,-1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,-1,1,1,0,1,1,1,1,1,-1,1,1,1],[1,-1,1,1,1,1,1,1,1,-1,1,1,-1,1,-1,-1,0,0,1,1,0,1,1,1,-1,1,-1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,-1,1],[-1,1,1,1,1,1,1,1,1,1,1,1,1,0,-1,1,1,1,1,1,1,1,-1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,-1,-1,-1,-1,1,1,1,1],[1,-1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,0,1,-1,1,-1,0,1,-1,1,1,1,-1,-1,1,1,-1,-1,0,-1,1,1,1,1,1,1,-1,1,1],[-1,1,1,1,1,1,1,0,-1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,1,-1,-1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,-1,1,1,1,1,-1,1,-1,1,1,1,-1,1,1,1,1,1,1,1,0,1,1,-1,1,1,1,1,1,1,1,1,1,1,-1,1,1,-1,1,1,1,1,1,1,1,1,-1,1],[1,1,1,-1,1,1,-1,1,0,1,-1,-1,1,1,1,1,1,1,1,1,0,-1,1,1,1,1,1,1,1,1,0,0,1,1,1,-1,1,0,1,-1,0,1,1,1,1,1,1,0,1,-1],[0,1,1,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,-1,1,-1,1,1,1,1,1,1,1,1,-1,1,-1,1,1,1,1,1,1,-1,1,0,-1,1,0,1,1,1,-1,-1],[1,1,1,1,1,1,1,-1,1,1,1,1,1,1,1,-1,1,0,1,1,1,-1,1,1,0,1,1,-1,-1,1,1,1,-1,1,-1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,1,1],[0,1,1,1,1,1,1,1,1,1,-1,1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,-1,1,1],[0,1,-1,0,1,1,1,-1,-1,1,1,1,1,0,1,1,-1,1,-1,-1,0,1,-1,0,1,1,1,1,1,-1,1,1,-1,1,1,1,1,-1,1,1,1,1,1,0,1,1,1,1,-1,1],[1,1,1,0,-1,-1,1,1,1,1,0,1,0,1,-1,1,0,1,1,1,1,1,0,1,1,-1,1,1,1,1,1,1,1,1,1,1,-1,1,1,0,-1,1,1,1,1,1,0,1,1,1]]
# print(solve741(grid))

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

def convert_string_to_nodes_array(string):
    t = string[1:-1].split(',')
    rs = []
    for x in t:
        if x != 'null': rs.append(int(x))
        else: rs.append(None)
    return rs

def build_tree_from_array(arr):
    nodes = []
    for v in arr:
        n = None
        if v is not None:
            n = TreeNode(v)
        nodes.append(n)

    l = 1
    r = 2
    for i in range(len(nodes)):
        if nodes[i] is not None:
            if l < len(nodes):
                nodes[i].left = nodes[l]
            if r < len(nodes):
                nodes[i].right = nodes[r]
            l += 2
            r += 2
    return nodes[0]

def print_tree(root):
    rs = []
    stack = [root]
    while stack:
        it = stack.pop(0)
        if it is not None:
            rs.append(it.val)
            #if it.left is not None or it.right is not None:
            stack.append(it.left)
            stack.append(it.right)
        else:
            rs.append(None)
    return rs

def is_insufficient(nodes, node_id, limit):
    for x in nodes[node_id]:
        if x >= limit:
            return False
    return True
def find_path(nodes, node, node_id, sum, path):
    path.append(node_id)
    if node.left is None and node.right is None:
        x = sum+node.val
        for nid in path:
            if nid not in nodes:
                nodes[nid] = [x]
            else:
                nodes[nid].append(x)
    else:
        if node.left is not None:
            find_path(nodes, node.left, node_id*2+1, sum+node.val, path)
        if node.right is not None:
            find_path(nodes, node.right, node_id*2+2, sum+node.val, path)
    path.pop(-1)

def solve1080(root, limit):
    nodes = {}
    find_path(nodes, root, 0, 0, [])
    # print(nodes)
    if is_insufficient(nodes, 0, limit):
        return None
    q = [(0, root)]
    while q:
        id, node = q.pop(0)
        if node.left is not None:
            if is_insufficient(nodes, id*2+1, limit):
                node.left = None
            else:
                q.append((id*2+1, node.left))
        if node.right is not None:
            if is_insufficient(nodes, id*2+2, limit):
                node.right = None
            else:
                q.append((id*2+2, node.right))
    return root


string = '[5,4,8,11,null,17,4,7,1,null,null,5,3]'
limit = 22
root = build_tree_from_array(convert_string_to_nodes_array(string))
print(print_tree(root))
print(print_tree(solve1080(root, limit)))


