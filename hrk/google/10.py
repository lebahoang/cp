# def one(arr):
#     tarr = []
#     for i in arr:
#         tarr.append(i)
#         if i == 0:
#             tarr.append(0)
#     for i in range(len(arr)):
#         arr[i] = tarr[i]

# def assign_to_a(a,b,i):
#     c = 0
#     for x,y in zip(a,b):
#         if x != i and y != i:
#             return -1
#         if x == i:
#             continue
#         else:
#             c += 1
#     return c


# def two(a, b):
#     minV = -1
#     for i in range(1, 7):
#         t1 = assign_to_a(a,b,i)
#         t2 = assign_to_a(b,a,i)
#         if t1 != -1 and (minV == -1 or t1 < minV):
#             minV = t1
#         if t2 != -1 and (minV == -1 or t2 < minV):
#             minV = t2
#     return minV

# import re
# def one(s):
#     t = ''
#     for i in s:
#         if re.match('[a-zA-Z0-9]', i):
#             t += i.lower()
#     i = 0
#     j = len(t)-1
#     while i < j:
#         if t[i] != t[j]:
#             return False
#         i += 1
#         j -= 1
#     return True

# print(one('race a ca'))

# def check(s):
#     t = s
#     ind = []
#     i = 0
#     j = len(t)-1
#     while i < j:
#         if t[i] != t[j]:
#             ind.append((i,j))
#             return ind
#         i += 1
#         j -= 1
#     return ind

# def solve680(s):
#     n = len(s)
#     ind = check(s)
#     print(ind)
#     if len(ind) == 0:
#         return True
#     t1 = []
#     t2 = []
#     for i,x in enumerate(s):
#         if i != ind[0][0] and i != ind[0][1]:
#             t1.append(x)
#             t2.append(x)
#         elif i != ind[0][0]:
#             t2.append(x)
#         else:
#             t1.append(x)
#     ind1 = check(t1)
#     ind2 = check(t2)
#     if len(ind1) == 0 or len(ind2) == 0:
#         return True
#     return False
    

# print(solve680('acadaa'))
# def go(num, ind, cur_number, cur_last_sum, temp_sum, temp_string, rs, target):
#     if ind == len(num):
#         if temp_sum == target:
#             rs.append(temp_string)
#         return

#     tt = int(num[ind])
#     if cur_number != 0:
#         if cur_number == cur_last_sum and cur_last_sum < 0:
#             a = (cur_number*10-tt)
#         else:
#             a = (cur_number*10+tt)
#         b = (cur_last_sum // cur_number)*a
#         x = (temp_sum - cur_last_sum) + b
#         go(num, ind+1, a, b, x, temp_string+num[ind] ,rs ,target)
        

#     go(num, ind+1, tt, tt, temp_sum+tt, temp_string+'+'+num[ind], rs, target)
#     go(num, ind+1, -tt, -tt, temp_sum-tt ,temp_string+'-'+num[ind], rs, target)

#     a = cur_last_sum*tt
#     b = (temp_sum - cur_last_sum) + a
#     go(num, ind+1, tt, a, b, temp_string+'*'+num[ind], rs, target)

# def solve282(num, target):
#     if num == '':
#         return []
#     seqs = []
#     go(num, 1, int(num[0]), int(num[0]), int(num[0]), num[0], seqs, target)
#     return seqs


# print(solve282('1000000009', 9))
# print(solve282('1234', 235))
# print(solve282('00', 0))
# print(solve282('123456789', 45))
# print(solve282('3456237490', 9191))

# def reverse_a_word(word):
#     t = ''
#     for w in word[::-1]:
#         t += w
#     return t
# def one(s):
#     words = s.split(' ')
#     rs = []
#     for word in words:
#         rs.append(reverse_a_word(word))
#     return ' '.join(rs)

# print(one("abc"))


# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

# def two(head):
#     pairs = []
#     h = head
#     while h is not None:
#         h_next = h.next
#         h_next_next = None
#         if h_next is not None:
#             h_next_next = h_next.next
#         pairs.append((h, h_next))
#         h = h_next_next

#     # print(pairs)
#     for n,nn in pairs:
#         if nn is not None:
#             nn.next = n
#     for i in range(len(pairs)):
#         if i < len(pairs)-1:
#             if pairs[i+1][1] is not None:
#                 pairs[i][0].next = pairs[i+1][1]
#             else:
#                 pairs[i][0].next = pairs[i+1][0]
#         else:
#             pairs[i][0].next = None

#     if len(pairs) == 0: return None
#     if pairs[0][1] is not None: return pairs[0][1]
#     return pairs[0][0]

# a = ListNode(1)
# b = ListNode(2)
# c = ListNode(3)
# d = ListNode(4)

# a.next = b
# b.next = c
# c.next = d

# x = two(None)
# t = x
# while t is not None:
#     print(t.val)
#     t = t.next

# def go(n, m, board, i, j, w, went, stop, dwords, visited, rs):
#     x = dwords.get(w, 0)
#     if x == 0:
#         return
#     elif x == 2:
#         if w not in rs:
#             rs[w] = 1

#     if went+1 <= stop:
#         if i-1 >= 0 and visited[i-1][j] == 0:
#             visited[i-1][j] = 1
#             go(n,m,board,i-1,j,w+board[i-1][j],went+1,stop,dwords,visited,rs)
#             visited[i-1][j] = 0
#         if i+1 < n and visited[i+1][j] == 0:
#             visited[i+1][j] = 1
#             go(n,m,board,i+1,j,w+board[i+1][j],went+1,stop,dwords,visited,rs)
#             visited[i+1][j] = 0
#         if j-1 >= 0 and visited[i][j-1] == 0:
#             visited[i][j-1] = 1
#             go(n,m,board,i,j-1,w+board[i][j-1],went+1,stop,dwords,visited,rs)
#             visited[i][j-1] = 0
#         if j+1 < m and visited[i][j+1] == 0:
#             visited[i][j+1] = 1
#             go(n,m,board,i,j+1,w+board[i][j+1],went+1,stop,dwords,visited,rs)
#             visited[i][j+1] = 0

# def three(board, words):
#     d = {}
#     dwords = {}
#     for w in words:
#         t = ''
#         for ch in w[:-1]:
#             t += ch
#             if t not in dwords:
#                 dwords[t] = 1
#         dwords[w] = 2
#         if w[0] in d:
#             d[w[0]] = max(d[w[0]], len(w))
#         else:
#             d[w[0]] = len(w)

#     rs = {}
#     n = len(board)
#     m = len(board[0])
#     # print(d, n, m, len(words), dwords)
#     visited = [[0 for j in range(m)] for i in range(n)]
#     for i in range(n):
#         for j in range(m):
#             if board[i][j] not in d: continue
#             visited[i][j] = 1
#             go(n, m, board, i, j, board[i][j], 1, d[board[i][j]], dwords, visited, rs)
#             visited[i][j] = 0
#     return list(rs.keys())

# board = [
#   ['o','a','a','n'],
#   ['e','t','a','e'],
#   ['i','h','k','r'],
#   ['i','f','l','v']
# ]
# words = ["eat","oath"]

# board = [
#     ['a', 'b'],
#     ['c', 'd']
# ]

# words = ['acdb']

# board = [
#     ['a', 'a']
# ]

# words = ['aaa']

# board = [["a","b"],["c","d"]]
# words = ["ab","cb","ad","bd","ac","ca","da","bc","db","adcb","dabc","abb","acb"]


# board = [["b","a","a","b","a","b"],["a","b","a","a","a","a"],["a","b","a","a","a","b"],["a","b","a","b","b","a"],["a","a","b","b","a","b"],["a","a","b","b","b","a"],["a","a","b","a","a","b"]]
# words = ["bbaabaabaaaaabaababaaaaababb","aabbaaabaaabaabaaaaaabbaaaba","babaababbbbbbbaabaababaabaaa","bbbaaabaabbaaababababbbbbaaa","babbabbbbaabbabaaaaaabbbaaab","bbbababbbbbbbababbabbbbbabaa","babababbababaabbbbabbbbabbba","abbbbbbaabaaabaaababaabbabba","aabaabababbbbbbababbbababbaa","aabbbbabbaababaaaabababbaaba","ababaababaaabbabbaabbaabbaba","abaabbbaaaaababbbaaaaabbbaab","aabbabaabaabbabababaaabbbaab","baaabaaaabbabaaabaabababaaaa","aaabbabaaaababbabbaabbaabbaa","aaabaaaaabaabbabaabbbbaabaaa","abbaabbaaaabbaababababbaabbb","baabaababbbbaaaabaaabbababbb","aabaababbaababbaaabaabababab","abbaaabbaabaabaabbbbaabbbbbb","aaababaabbaaabbbaaabbabbabab","bbababbbabbbbabbbbabbbbbabaa","abbbaabbbaaababbbababbababba","bbbbbbbabbbababbabaabababaab","aaaababaabbbbabaaaaabaaaaabb","bbaaabbbbabbaaabbaabbabbaaba","aabaabbbbaabaabbabaabababaaa","abbababbbaababaabbababababbb","aabbbabbaaaababbbbabbababbbb","babbbaabababbbbbbbbbaabbabaa"]
# print(three(board, words))

# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
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

# class XNode:
#     def __init__(self, tn, parent):
#         self.tn = tn
#         self.parent = parent

# def find_path_to_root(start):
#     rs = []
#     stack = [start]
#     while stack:
#         it = stack.pop(-1)
#         rs.append(it.tn.val)
#         if it.parent is not None:
#             stack.append(it.parent)
#     return rs

# def one(root, p, q):
#     stack = [XNode(root, None)]
#     s = None
#     e = None
#     while stack:
#         it = stack.pop(-1)
#         if it.tn.val == p.val:
#             s = it
#         elif it.tn.val == q.val:
#             e = it

#         if it.tn.left is not None:
#             stack.append(XNode(it.tn.left, it))
#         if it.tn.right is not None:
#             stack.append(XNode(it.tn.right, it))
#     x = find_path_to_root(s)
#     y = find_path_to_root(e)
#     for i in x:
#         for j in y:
#             if i == j: return i
#     return -1


# arr = '[6,2,8,0,4,7,9,null,null,3,5]'
# root = build_tree_from_array(convert_string_to_nodes_array(arr))
# print(one(root, TreeNode(2), TreeNode(4)))


# def two(A, B):
#     mA = [0 for i in A]
#     mB = [0 for i in B]
#     rs = []
#     i = 0
#     j = 0
#     while True:
#         # print(i,j,rs)
#         if i == len(A) or j == len(B):
#             break

#         if B[j][0] >= A[i][0] and B[j][0] <= A[i][1]:
#             if B[j][1] <= A[i][1]:
#                 rs.append(B[j])
#                 mA[i] = 1
#                 j += 1
#             else:
#                 rs.append([B[j][0], A[i][1]])
#                 mB[j] = 1
#                 i += 1
#         elif A[i][0] >= B[j][0] and A[i][0] <= B[j][1]:
#             if A[i][1] <= B[j][1]:
#                 rs.append(A[i])
#                 mB[j] = 1
#                 i += 1
#             else:
#                 rs.append([A[i][0], B[j][1]])
#                 mA[i] = 1
#                 j += 1
#         elif A[i][0] > B[j][1]:
#             # if mB[j] == 0:
#             #     rs.append(B[j])
#             j += 1
#         elif B[j][1] > A[i][1]:
#             # if mA[i] == 0:
#             #     rs.append(A[i])
#             i += 1
#     return rs

# A = [[0,2],[5,10],[13,23],[24,25]]
# B = [[1,5],[8,12],[15,24],[25,26]]
# print(two(A, B))


# A = [[6,9], [11,12]]
# B = [[0,2], [7,15]]
# print(two(A, B))

# def one(s):
#     rs = -1
#     d = {}
#     for i in range(len(s)):
#         if s[i] not in d:
#             d[s[i]] = [i]
#         else:
#             d[s[i]].append(i)
    

#     rs = -1
#     for v in d.values():
#         if len(v) == 1:
#             if rs == -1 or v[0] < rs:
#                 rs = v[0]
#     return rs

# print(one('loveleetcode'))

# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

# def two(head):
#     if head is None: return None
#     new_head = None
#     t = head
#     t_next = head.next
#     while t is not None:
#         if t is not None: new_head = t
#         if t_next is not None:
#             tt = t_next.next
#             t_next.next = t
#             t = t_next
#             t_next = tt
#         else:
#             t = t_next
#     head.next = None  
#     return new_head


# a = ListNode(1)
# b = ListNode(2)
# c = ListNode(3)
# d = ListNode(4)
# a.next = b
# b.next = c
# c.next = d

# t = two(a)
# while t is not None:
#     print(t.val)
#     t = t.next

# def find(a, l, r):
#     if l >= r: return -1
#     mid = (l+r)//2
#     print(mid, l, r)
#     if mid == 0:
#         if mid+1 < len(a) and a[mid] > a[mid+1]:
#             return mid
#         return -1
#     if mid == len(a)-1:
#         return -1
#     if a[mid] > a[mid+1]:
#         return mid
#     x = find(a, l, mid)
#     if x != -1: return x
#     y = find(a, mid+1, r)
#     if y != -1: return y
#     return -1

# def search(a, l, r, target):
#     if l > r: return -1
#     mid = (l+r)//2
#     if a[mid] == target: return mid
#     if a[mid] < target:
#         return search(a, mid+1, r, target)
#     return search(a, l, mid-1, target)

# def three(a, target):
#     ind =  find(a, 0, len(a)-1)
#     if ind == -1:
#         return search(a, 0, len(a)-1, target)
    
#     x = search(a, 0, ind, target)
#     y = search(a, ind+1, len(a)-1, target)
#     if x != -1: return x
#     elif y != -1: return y
#     return -1

# def one(prices):
#     mins = [prices[0]]
#     for i in prices[1:]:
#         mins.append(min(i, mins[-1]))
#     maxV = 0
#     for i in range(1, len(prices)):
#         maxV = max(maxV, prices[i]-mins[i-1])
#     return maxV

# print(one([7,1,5,3,6,4]))
# print(one([7,6,4,3,1]))

# def one(A):
#     if len(A) < 3: return -1
#     left = [True]
#     for i in range(1, len(A)):
#         if left[-1] and A[i] > A[i-1]:
#             left.append(True)
#         else:
#             left.append(False)

#     right = [False]*len(A)
#     right[len(A)-1] = True
#     for i in range(len(A)-2, -1, -1):
#         if right[i+1] and A[i] > A[i+1]:
#             right[i] = True
#         else:
#             right[i] = False
#     # print(left, right)
#     for i in range(len(A)):
#         if left[i] and right[i]:
#             return i
#     return -1

# print(one([0,2,1,0]))


# def find(a, l, r):
#     if l >= r: return -1
#     mid = (l+r)//2
#     # print(mid, l, r)
#     if mid == 0 or mid == a.length()-1:
#         return -1 
#     if a.get(mid) > a.get(mid-1) and a.get(mid) > a.get(mid+1):
#         return mid
#     x = find(a, l, mid)
#     if x != -1: return x
#     y = find(a, mid+1, r)
#     if y != -1: return y
#     return -1

# def search1(a, l, r, target):
#     if l > r: return -1
#     mid = (l+r)//2
#     if a.get(mid) == target: return mid
#     if a.get(mid) < target:
#         return search1(a, mid+1, r, target)
#     return search1(a, l, mid-1, target)

# def search2(a, l, r, target):
#     if l > r: return -1
#     mid = (l+r)//2
#     if a.get(mid) == target: return mid
#     if a.get(mid) < target:
#         return search2(a, l, mid-1, target)
#     return search2(a, mid+1, r, target)
# def two(a, target):
#     ind = find(a, 0, len(a)-1)
#     if ind == -1:
#         return search1(a, 0, len(a)-1, target)
#     else:
#         x = search1(a, 0, ind, target)
#         if x != -1: return x
#         y = search2(a, ind+1, len(a)-1, target)
#         if y != -1: return y
#         return -1
# class A():
#     def __init__(self, a):
#         self.a = a
#         self.call = 0
#     def get(self, k):
#         self.call += 1
#         print('Call', self.call)
#         return self.a[k]
#     def length(self):
#         return len(self.a)

# def search1(a, l, r, target):
#     if l > r: return -1
#     mid = (l+r)//2
#     if a.get(mid) == target: return mid
#     if a.get(mid) < target:
#         return search1(a, mid+1, r, target)
#     return search1(a, l, mid-1, target)

# def find(a, l, r, target, rs, d):
#     if l > r: return -1
#     mid = (l+r)//2
#     midv = a.get(mid)
#     # print(l,r,mid)
#     if midv == target:
#         return mid
#     if mid == 0:
#         # if mid+1 < a.length():
#         #     return find(a, mid+1, r, target, rs)
#         return -1
#     if mid == a.length()-1:
#         # if mid-1 >= 0:
#         #     return find(a, l, mid-1, target, rs)
#         return -1
#     midp = a.get(mid-1)
#     midn = a.get(mid+1)
#     if midv > midp and midv < midn:
#         if midv < target:
#             x = find(a, mid+1, r, target, rs)
#             if x != -1: return x
#             return find(a, l, mid-1, target, rs)
#         else:
#             x = find(a, l, mid-1, target, rs)
#             if x != -1: return x
#             return find(a, mid+1, r, target, rs)
#     elif midv > midn and midv < midp:
#         if midv < target:
#             x = find(a, l, mid-1, target, rs)
#             if x != -1: return x
#             return find(a, mid+1, r, target, rs)
#         else:
#             x = find(a, mid+1, r, target, rs)
#             if x != -1: return x
#             return find(a, l, mid-1, target, rs)
#     else:
#         rs.append(mid)
#         if midv < target:
#             return -1
#         x = find(a, l, mid-1, target, rs)
#         if x != -1: return x
#         return find(a, mid+1, r, target, rs)


        
# def two(target, a):
#     n = a.length()
#     print(n)
#     m = []
#     ind = find(a, 0, n-1, target, m)
#     print(ind, m, a.call)
#     if len(m) == 0:
#         m = ind
#     else:
#         m = m[0]
#     if ind >= m:
#         x = search1(a, 0, m-1, target)
#         if x != -1: return x
#         return ind
#     return ind
    

# arr = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82]
# a = A(arr)
# print(two(1, a))

# arr = [3,5,3,2,0]
# a = A(arr)
# print(two(5, a))



# arr = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2]
# a = A(arr)
# print(two(22, a))

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

def three(root, deletes):
    to_deleted = [False for i in range(1, 1001)]
    for i in deletes:
        to_deleted[i] = True
    rs = []
    if not to_deleted[root.val]:
        rs.append(root)
    queue = [root]
    while queue:
        it = queue.pop(0)
        if it.left is not None:
            queue.append(it.left)
            if to_deleted[it.left.val]:
                it.left = None
        if it.right is not None:
            queue.append(it.right)
            if to_deleted[it.right.val]:
                it.right = None

        if to_deleted[it.val]:
            if it.left is not None:
                if not to_deleted[it.left.val]:
                    rs.append(it.left)
            if it.right is not None:
                if not to_deleted[it.right.val]:
                    rs.append(it.right)

    for i in rs:
        print(i.val)
    return rs

root = build_tree_from_array(convert_string_to_nodes_array('[1,2,3,4,5,6,7]'))
print(three(root, [3,5]))

























