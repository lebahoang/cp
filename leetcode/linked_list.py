class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

def build_linked_list_from_arr(arr):
    if not arr:
        return None
    root = ListNode(arr[0])
    cur = root
    for i in arr[1:]:
        x = ListNode(i)
        cur.next = x
        cur = x
    return root
def print_linked_list(head):
    t = []
    r = head
    while r is not None:
        t.append(r.val)
        r = r.next
    return t


