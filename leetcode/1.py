# import sys

# def p2_go(p2, s, d, total):
#     t = p2
#     ttotal = total
#     while t < len(s):
#         if s[t] in d:
#             d[s[t]] -= 1
#             if d[s[t]] >= 0:
#                 ttotal -= 1
#                 if ttotal == 0:
#                     break
#         t += 1
#     return t, ttotal



# # s = 'ADOBECOBEBANC'
# # t = 'BOC'
# # s = "bbaac"
# # t = "aba"

# total = len(t)
# d = {}
# for i in t:
#     if i not in d: d[i] = 1
#     else: d[i] += 1

# minV = -1
# minS = ''
# p1 = p2 = 0


# while p2 < len(s):
#     p2, total = p2_go(p2, s, d, total)
#     # print('p1', p1, 'p2', p2, d)
#     if p2 == len(s): break
#     for t in range(p1, p2+1):
#         if t-1 >= p1 and s[t-1] in d:
#             d[s[t-1]] += 1
#             if d[s[t-1]] > 0:
#                 total += 1
#                 break
#         if total == 0:
#             if minV == -1 or minV > p2-t+1:
#                 # print(s[t:p2+1], d)
#                 minV = p2-t+1
#                 minS = s[t:p2+1]


#     p1 = t
#     p2 += 1
# print(minS)



# def one(s):
#     c = 0
#     n = len(s)
#     for i in range(n):
#         c += 1
#         ii = i-1
#         jj = i+1
#         while ii >= 0 and jj < n and s[ii] == s[jj]:
#             c += 1
#             ii -= 1
#             jj += 1

#         ii = i
#         jj = i+1
#         while ii >= 0 and jj < n and s[ii] == s[jj]:
#             c += 1
#             ii -= 1
#             jj += 1
#     return c

# print(one('aaa'))

# def find_min(arr):
#     rs = []
#     for i in range(len(arr)):
#         if i == 0:
#             rs.append((arr[i], i))
#         else:
#             if arr[i] < rs[-1][0]:
#                 rs.append((arr[i], i))
#             else:
#                 rs.append((rs[-1][0], rs[-1][1]))
#     return rs

# def find_max(arr):
#     rs = []
#     for i in range(len(arr)):
#         if i == 0:
#             rs.append((arr[i], i))
#         else:
#             if arr[i] > rs[-1][0]:
#                 rs.append((arr[i], i))
#             else:
#                 rs.append((rs[-1][0], rs[-1][1]))
#     return rs
# def two(arr1, arr2):
#     t1_min = find_min(arr1)
#     t1_max = find_max(arr1)
#     t2_min = find_min(arr2)
#     t2_max = find_max(arr2)

#     n = len(arr1)
#     maxV = -1
#     for i in range(1, n):
#         t = t1_min[i-1][1]
#         x = abs(arr1[i]-t1_min[i-1][0]) + abs(arr2[i]-arr2[t]) + abs(i-t)
#         t = t1_max[i-1][1]
#         y = abs(arr1[i]-t1_max[i-1][0]) + abs(arr2[i]-arr2[t]) + abs(i-t)
#         t = t2_min[i-1][1]
#         z = abs(arr1[i]-arr1[t]) + abs(arr2[i]-t2_min[i-1][0]) + abs(i-t)
#         t = t2_max[i-1][1]
#         k = abs(arr1[i]-arr1[t]) + abs(arr2[i]-t2_max[i-1][0]) + abs(i-t)
#         m = abs(arr1[i]-arr1[0]) + abs(arr2[i]-arr2[0]) + i
#         if maxV < max(x,y,z,k,m):
#             maxV = max(x,y,z,k,m)
#     return maxV




# arr1 = [1,2,3,4]
# arr2 = [-1,4,5,6]
# arr1 = [1,-2,-5,0,10]
# arr2 = [0,-2,-1,-7,-4]
# print(two(arr1, arr2))



# import sys
# sys.setrecursionlimit(1500)
# def go(i, j, s1, s2, dp):
#     if i < 0 and j < 0:
#         return ''
#     if i < 0:
#         dp[i, j] = s2[:j+1]
#         return dp[i,j]
#     if j < 0:
#         dp[i, j] = s1[:i+1]
#         return dp[i,j]
#     if (i,j) in dp:
#         return dp[i,j]

#     if s1[i] == s2[j]:
#         dp[i,j] = go(i-1, j-1, s1, s2, dp) + s1[i]
#         return dp[i,j]
#     else:
#         # t = go(i-1, j-1, s1, s2, dp) + s1[i] + s2[j]

#         tt = go(i-1, j, s1, s2, dp) + s1[i]
#         ttt = go(i, j-1, s1, s2, dp) + s2[j]
#         # print(i,j,t,tt,ttt)
#         x = min(len(tt), len(ttt))
#         if x == len(tt):
#             dp[i,j] = tt
#         elif x == len(ttt):
#             dp[i,j] = ttt
#         return dp[i,j]
# def three(s1, s2):
#     n = len(s1)
#     m = len(s2)
#     dp = {}
#     rs = go(n-1, m-1, s1, s2, dp)
#     print(len(rs), 'KQ')
#     print(len(dp.keys()))
#     return rs

# s1 = 'abac'
# s2 = 'cab'
# s1 = "atdznrqfwlfbcqkezrltzyeqvqemikzgghxkzenhtapwrmrovwtpzzsyiwongllqmvptwammerobtgmkpowndejvbuwbporfyroknrjoekdgqqlgzxiisweeegxajqlradgcciavbpgqjzwtdetmtallzyukdztoxysggrqkliixnagwzmassthjecvfzmyonglocmvjnxkcwqqvgrzpsswnigjthtkuawirecfuzrbifgwolpnhcapzxwmfhvpfmqapdxgmddsdlhteugqoyepbztspgojbrmpjmwmhnldunskpvwprzrudbmtwdvgyghgprqcdgqjjbyfsujnnssfqvjhnvcotynidziswpzhkdszbblustoxwtlhkowpatbypvkmajumsxqqunlxxvfezayrolwezfzfyzmmneepwshpemynwzyunsxgjflnqmfghsvwpknqhclhrlmnrljwabwpxomwhuhffpfinhnairblcayygghzqmotwrywqayvvgohmujneqlzurxcpnwdipldofyvfdurbsoxdurlofkqnrjomszjimrxbqzyazakkizojwkuzcacnbdifesoiesmkbyffcxhqgqyhwyubtsrqarqagogrnaxuzyggknksrfdrmnoxrctntngdxxechxrsbyhtlbmzgmcqopyixdomhnmvnsafphpkdgndcscbwyhueytaeodlhlzczmpqqmnilliydwtxtpedbncvsqauopbvygqdtcwehffagxmyoalogetacehnbfxlqhklvxfzmrjqofaesvuzfczeuqegwpcmahhpzodsmpvrvkzxxtsdsxwixiraphjlqawxinlwfspdlscdswtgjpoiixbvmpzilxrnpdvigpccnngxmlzoentslzyjjpkxemyiemoluhqifyonbnizcjrlmuylezdkkztcphlmwhnkdguhelqzjgvjtrzofmtpuhifoqnokonhqtzxmimp"
# s2 = "xjtuwbmvsdeogmnzorndhmjoqnqjnhmfueifqwleggctttilmfokpgotfykyzdhfafiervrsyuiseumzmymtvsdsowmovagekhevyqhifwevpepgmyhnagjtsciaecswebcuvxoavfgejqrxuvnhvkmolclecqsnsrjmxyokbkesaugbydfsupuqanetgunlqmundxvduqmzidatemaqmzzzfjpgmhyoktbdgpgbmjkhmfjtsxjqbfspedhzrxavhngtnuykpapwluameeqlutkyzyeffmqdsjyklmrxtioawcrvmsthbebdqqrpphncthosljfaeidboyekxezqtzlizqcvvxehrcskstshupglzgmbretpyehtavxegmbtznhpbczdjlzibnouxlxkeiedzoohoxhnhzqqaxdwetyudhyqvdhrggrszqeqkqqnunxqyyagyoptfkolieayokryidtctemtesuhbzczzvhlbbhnufjjocporuzuevofbuevuxhgexmckifntngaohfwqdakyobcooubdvypxjjxeugzdmapyamuwqtnqspsznyszhwqdqjxsmhdlkwkvlkdbjngvdmhvbllqqlcemkqxxdlldcfthjdqkyjrrjqqqpnmmelrwhtyugieuppqqtwychtpjmloxsckhzyitomjzypisxzztdwxhddvtvpleqdwamfnhhkszsfgfcdvakyqmmusdvihobdktesudmgmuaoovskvcapucntotdqxkrovzrtrrfvoczkfexwxujizcfiqflpbuuoyfuoovypstrtrxjuuecpjimbutnvqtiqvesaxrvzyxcwslttrgknbdcvvtkfqfzwudspeposxrfkkeqmdvlpazzjnywxjyaquirqpinaennweuobqvxnomuejansapnsrqivcateqngychblywxtdwntancarldwnloqyywrxrganyehkglbdeyshpodpmdchbcc"
# s1 = 'a'*1000
# s2 = 'a'*1000
# print(len(s1), len(s2))
# print(three(s1, s2))




class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

def build_linked_list_from_arr(arr):
    if not arr:
        return None
    head = ListNode(arr[0])
    cur = head
    for i in arr[1:]:
        x = ListNode(i)
        cur.next = x
        cur = x
    return head
def print_linked_list(head):
    t = []
    r = head
    while r is not None:
        t.append(r.val)
        r = r.next
    print(t)

def analysis_linked_list(head):
    d = {}
    t = head
    i = 0
    cursum = 0
    while t is not None:
        cursum += t.val
        if cursum not in d:
            d[cursum] = [i]
        else:
            d[cursum].append(i)
        t = t.next
        i += 1
    return d
def remove_nodes(head, s, e):
    i = 0
    t = head
    snode = None
    old_enode = None
    enode = None
    while t is not None:
        if i == s:
            snode = t
        elif i == e:
            old_enode = t
        elif i == e+1:
            enode = t
        t = t.next
        i += 1
    if snode is None:
        head = enode
    else:
        snode.next = enode
    old_enode.next = None
    return head
def is_linked_list_valid(d):
    for k,v in d.items():
        if k == 0:
            return False
        if len(v) > 1:
            return False
    return True

def solve(head):
    while True:
        d = analysis_linked_list(head)
        if is_linked_list_valid(d):
            break
        for k,v in d.items():
            if k == 0:
                v = [-1]+v
            if len(v) > 1:
                head = remove_nodes(head, v[0], v[-1])
                break
    return head



arr = [1, -1]
head = build_linked_list_from_arr(arr)
# print_linked_list(head)
print_linked_list(solve(head))
# print(analysis_linked_list(head))


