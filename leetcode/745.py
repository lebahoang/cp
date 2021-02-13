def find_max_in_2sorted_lists(a,b):
    rs = -1
    j = 0
    for i in a:
        while j < len(b):
            if i[0] > b[j][0]:
                j += 1
            else:
                if i[0] == b[j][0]:
                    rs = i[0]
                break
    return rs

class TrieNode():
    def __init__(self):
        self.keys = 'abcdefghijklmnopqrstuvwxyz'
        self.child_nodes = {}
        # for k in self.keys:
        #     self.child_nodes[k] = None
        self.val = None

def update_trie(root, word, w):
    n = root
    for c in word:
        if c in n.child_nodes:
            n = n.child_nodes[c]
        else:
            x = TrieNode()
            n.child_nodes[c] = x
            n = x

    n.val = (w, word)
    return root
def query(root, string):
    n = root
    for c in string:
        if c in n.child_nodes:
            n = n.child_nodes[c]
        else:
            n = None
            break
    if n is None: return []

    collections = []
    queue = [n]
    while queue:
        it = queue.pop(0)
        if it.val is not None:
            collections.append(it.val)
        for child in it.child_nodes.values():
            queue.append(child)
    # print(collections)
    return sorted(collections)

def foo(prefix, suffix, prefix_trie, suffix_trie):
    a = query(prefix_trie, prefix)
    suffix = suffix[::-1]
    b = query(suffix_trie, suffix)
    print(a, b, 'aaaaa')
    return find_max_in_2sorted_lists(a,b)


words = ['aaaaa', 'aabaa', 'aacaa', 'aadaa', 'aafaa']
prefix = 'aa'
suffix = 'baa'
prefix_trie = TrieNode()
suffix_trie = TrieNode()

for i, word in enumerate(words):
    prefix_trie = update_trie(prefix_trie, word, i)
    reversed_word = word[::-1]
    suffix_trie =  update_trie(suffix_trie, reversed_word, i)

print(foo(prefix, suffix, prefix_trie, suffix_trie))


        









            