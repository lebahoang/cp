import sys

class Node():
    def __init__(self, char, value, parent):
        self.char = char
        self.value = value
        self.parent = parent
        self.children = {}
    def add_value(self, amount):
        self.value += amount
    def subtract_value(self, amount):
        self.value -= amount
    def print(self):
        parent = self.parent.char if self.parent is not None else ''
        print(self.char, self.value, parent, self.children)
class Trie():
    def __init__(self):
        self.leaves = []
        self.root = Node('', 0, None)

    def print(self):
        queue = [self.root]
        while queue:
            it = queue.pop(0)
            it.print()
            for c in it.children.values():
                queue.append(c)
    def insert(self, word):
        i = 0
        t = self.root
        while True:
            w = word[i]
            if w in t.children:
                t.children[w].add_value(1)
            else:
                t.children[w] = Node(w, 1, t)
            
            t = t.children[w]
            i += 1
            if i == len(word):
                self.leaves.append(t)
                break


    def subtract_backward(self, node, value):
        # subtract backward to root
        c = node
        while c is not None:
            if c.char != '':
                c.subtract_value(value)
            c = c.parent
    def is_stop(self):
        # self.print()
        queue = [c for c in self.root.children.values()]
        while queue:
            it = queue.pop()
            if it.value == 2:
                return False
            for c in it.children.values():
                queue.append(c)
        return True

    def query(self):
        total = 0
        for l in self.leaves:
            queue = [l]
            while queue:
                it = queue.pop()
                if it.value == 2:
                    total += 1
                    self.subtract_backward(it, 2)
                if it.parent is not None:
                    queue.append(it.parent)


        # iterate last time to collect all remaining node (nodes whose value > 2)
        for l in self.leaves:
            queue = [l]
            while queue:
                it = queue.pop()
                if it.value >= 2:
                    total += 1
                    self.subtract_backward(it, 2)
                    it.value = 0
                if it.parent is not None:
                    queue.append(it.parent)
        return total*2






t = int(sys.stdin.readline().strip())
for case in range(t):
    trie = Trie()
    n = int(sys.stdin.readline().strip())
    for _ in range(n):
        word = sys.stdin.readline().strip()
        trie.insert(word[::-1])

    trie.print()
    total = trie.query()
    #print('--------------------')
    #trie.print()
    print('Case #{:d}: {:d}'.format(case+1, total))
        

