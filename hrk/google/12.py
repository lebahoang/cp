# def one(A):
#     n = len(A)
#     dp = [{} for i in range(n)]
#     maxV = 0
#     for i in range(1, n):
#         for j in range(i):
#             if A[i]-A[j] in dp[j]:
#                 if A[i]-A[j] in dp[i]:
#                     dp[i][A[i]-A[j]] = max(dp[i][A[i]-A[j]], dp[j][A[i]-A[j]]+1)
#                 else:
#                     dp[i][A[i]-A[j]] = dp[j][A[i]-A[j]]+1
#             else:
#                 dp[i][A[i]-A[j]] = 1
#             if maxV < dp[i][A[i]-A[j]]:
#                 maxV = dp[i][A[i]-A[j]]

#     return maxV+1


# A = [3,6,9,12]
# A = [9,4,7,2,10]
# A = [20,1,15,3,10,5,8]
# print(one(A))


# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

# def two(root):
#     queue = [root]
#     rs = []
#     while queue:
#         it = queue.pop(0)
#         if it is not None:
#             rs.append(it.val)
#             queue.append(it.left)
#             queue.append(it.right)
#         else:
#             rs.append(it)
#         print(rs)

#     # print(rs)
#     saw_none = False
#     for v in rs:
#         if v is None:
#             saw_none = True
#         else:
#             if saw_none: return False
#     return True


# a = TreeNode(1)
# b = TreeNode(2)
# c = TreeNode(3)
# a.left = b
# a.right = c
# d = TreeNode(4)
# e = TreeNode(5)
# b.left = d
# b.right = e
# f = TreeNode(6)
# c.left = f

# a = TreeNode(1)
# b = TreeNode(2)
# c = TreeNode(3)
# a.left = b
# a.right = c
# d = TreeNode(4)
# e = TreeNode(5)
# b.left = d
# b.right = e
# f = TreeNode(7)
# c.right = f

# print(two(a))


# def one(image, sr, sc, newColor):
#     sv = image[sr][sc]
#     n = len(image)
#     m = len(image[0])
#     new_image = [[image[i][j] for j in range(m)] for i in range(n)]
#     stack = [(sr, sc)]
#     visited = [[0 for j in range(m)] for i in range(n)]
#     while stack:
#         x,y = stack.pop(-1)
#         if image[x][y] == sv:
#             new_image[x][y] = newColor
#         visited[x][y] = 1
#         if x-1 >= 0 and visited[x-1][y] == 0 and image[x-1][y] == sv:
#             stack.append((x-1, y))
#         if x+1 < n and visited[x+1][y] == 0 and image[x+1][y] == sv:
#             stack.append((x+1, y))
#         if y-1 >= 0 and visited[x][y-1] == 0 and image[x][y-1] == sv:
#             stack.append((x, y-1))
#         if y+1 < m and visited[x][y+1] == 0 and image[x][y+1] == sv:
#             stack.append((x, y+1))
#     return new_image

# image = [[1,1,1],[1,1,0],[1,0,1]]
# sr = 1
# sc = 1
# newColor = 2
# print(one(image, sr, sc, newColor))

# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


# class Node:
#     def __init__(self, tree_node):
#         self.tn = tree_node
#         self.left = None
#         self.right = None
#         self.max_left = None
#         self.max_right = None
#         self.sum_from_root = 0

# def convert_string_to_nodes_array(string):
#     t = string[1:-1].split(',')
#     rs = []
#     for x in t:
#         if x != 'null': rs.append(int(x))
#         else: rs.append(None)
#     return rs
# def build_tree_from_array(arr):
#     nodes = []
#     for v in arr:
#         n = None
#         if v is not None:
#             n = TreeNode(v)
#         nodes.append(n)

#     l = 1
#     r = 2
#     for i in range(len(nodes)):
#         if nodes[i] is not None:
#             if l < len(nodes):
#                 nodes[i].left = nodes[l]
#             if r < len(nodes):
#                 nodes[i].right = nodes[r]
#             l += 2
#             r += 2
#     return nodes[0]
# def print_tree(root):
#     rs = []
#     stack = [root]
#     while stack:
#         it = stack.pop(0)
#         if it is not None:
#             rs.append(str(it.val))
#             stack.append(it.left)
#             stack.append(it.right)
#         else:
#             rs.append('None')


#     print(','.join(rs))

# def find_max_left_right_path(node, cur_sum):
#     if node.tn.left is None and node.tn.right is None:
#         node.max_left = cur_sum+node.tn.val
#         node.max_right = cur_sum+node.tn.val
#         return node.max_left

#     val_left = None
#     if node.tn.left is not None:
#         val_left = find_max_left_right_path(node.left, cur_sum+node.tn.val)
#         if node.max_left is None or node.max_left < val_left:
#             node.max_left = val_left
#     val_right = None
#     if node.tn.right is not None:
#         val_right = find_max_left_right_path(node.right, cur_sum+node.tn.val)
#         if node.max_right is None or node.max_right < val_right:
#             node.max_right = val_right

#     if val_left is None:
#         return val_right
#     if val_right is None:
#         return val_left
#     return max(val_left, val_right)

# def build_from_root(root):
#     new_root = Node(root)
#     new_root.sum_from_root = root.val
#     stack = [new_root]
#     while stack:
#         it = stack.pop(-1)
#         if it.tn.left is not None:
#             x = Node(it.tn.left)
#             it.left = x
#             stack.append(x)
#         if it.tn.right is not None:
#             x = Node(it.tn.right)
#             it.right = x
#             stack.append(x)
#     return new_root
# def two(root, limit):
#     new_root = build_from_root(root)
#     find_max_left_right_path(new_root, 0)
#     # print('------------')
#     stack = [new_root]
#     while stack:
#         it = stack.pop(-1)
#         if it.left is not None:
#             left = it.left
#             if (left.max_left is not None and left.max_left >= limit) or \
#                 (left.max_right is not None and left.max_right >= limit):
#                 it.tn.left = left.tn
#                 stack.append(left)
#             else:
#                 it.tn.left = None
#                 it.left = None
#         if it.right is not None:
#             right = it.right
#             if (right.max_left is not None and right.max_left >= limit) or \
#                 (right.max_right is not None and right.max_right >= limit):
#                 it.tn.right = right.tn
#                 stack.append(right)
#             else:
#                 it.tn.right = None
#                 it.right = None

#     if (new_root.max_left is not None and new_root.max_left >= limit) or \
#        (new_root.max_right is not None and new_root.max_right >= limit):
#         return new_root.tn
#     return None




# arr = '[5,4,8,11,null,17,4,7,1,null,null,5,3]'
# arr = '[1,2,-3,-5,null,4,null]'
# arr = '[1,null,6,9,4,0]'
# root = build_tree_from_array(convert_string_to_nodes_array(arr))
# print_tree(root)
# print('----------')
# limit = 10
# new_root = two(root, limit)
# print_tree(new_root)

def one():





