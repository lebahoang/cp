# import sys

# def cmp_func(a,b):
#   if len(a) < len(b): return -1
#   if len(a) > len(b): return 1
#   if a < b: return -1
#   if a > b: return 1
#   return 0


# n = int(sys.stdin.readline())
# arr = []
# for _ in xrange(n):
#   arr.append(sys.stdin.readline().strip())
# arr = sorted(arr, cmp = cmp_func)

# print '\n'.join(arr)

class Node():
    def __init__(self, x,y):
        self.x = x
        self.y = y
        self.down = None
        self.up = None
        self.right = None
        self.left = None
        
def distance(a, b):
    if a is None or b is None: return 0
    return int(((a.x-b.x)**2 + (a.y-b.y)**2)**0.5)
def build_graph():
    with open('x.txt', 'r') as f:
        nodes = {}
        for line in f.readlines():
            p = list(map(int, line.strip().split(' ')))
            n = m = None
            if (p[0], p[1]) not in nodes:
                n = Node(p[0], p[1])
                nodes[(p[0], p[1])] = n
            else:
                n = nodes[(p[0], p[1])]

            if (p[2], p[3]) not in nodes:
                m = Node(p[2], p[3])
                nodes[(p[2], p[3])] = m
            else:
                m = nodes[(p[2], p[3])]

            if p[0] == p[2] and p[1] < p[3]:
                n.up = m
                m.down = n
            elif p[0] == p[2] and p[1] > p[3]:
                n.down = m
                m.up = n
            elif p[1] == p[3] and p[0] < p[2]:
                n.right = m
                m.left = n
            else:
                n.left = m
                m.right = n
        return nodes.values()
def check_square(node, length):
    direction = 'r'
    cur_len = 0
    cur = node
    q = []
    if node.right is not None:
        q.append(node.right)
    while q:
        it = q.pop(0)
        cur_len += distance(cur, it)
        # print('cur_len', cur_len)
        if cur_len > length:
            return False
        if cur_len == length:
            if direction == 'r':
                direction = 'u'
                cur_len = 0
            elif direction == 'u':
                direction = 'l'
                cur_len = 0
            else:
                return True
        if direction == 'r':
            if it.right is not None:
                q.append(it.right)
        elif direction == 'u':
            if it.up is not None:
                q.append(it.up)
        else:
            if it.left is not None:
                q.append(it.left)
        cur = it
    return False

def count_square(node):
    c = 0
    length = 0
    cur = node
    q = []
    if node.down is not None:
        q.append(node.down)
    while q:
        it = q.pop(0)
        length += distance(it, cur)
        # print(q,it.x,it.y,length)
        if check_square(it, length):
            c += 1
        if it.down is not None:
            q.append(it.down)
        cur = it
    return c


def solve():
    nodes = build_graph()
    c = 0
    for node in nodes:
        tt = count_square(node)
        print(node.x, node.y,tt)
        c += tt
        print('-----------')
    return c

print(solve())

