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
    queue = [(root, 0)]
    t = []
    while queue:
        it, level = queue.pop(0)
        if t:
            if level != t[-1][1]:
                f = False
                for n, _ in t:
                    if n != None:
                        f = True
                        break
                if f:
                    for n, _ in t:
                        if n is not None: rs.append(n.val)
                        else: rs.append(n)
                t = [(it, level)]
            else:
                t.append((it, level))
        else:
            t.append((it, level))
        if it != None:
            queue.append((it.left, level+1))
            queue.append((it.right, level+1))
    return rs


# string = '[5,4,8,11,null,17,4,7,1,null,null,5,3]'
string = '[5,4,7,3,null,2,null,-1,null,9]'
root = build_tree_from_array(convert_string_to_nodes_array(string))
print(print_tree(root))