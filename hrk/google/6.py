# def solve1(A):
#     n = len(A)
#     minV = 0
#     cur = 0
#     while cur < n-1:
#         max_ind = cur+A[cur]
#         if max_ind >= n-1:
#             minV += 1
#             break

#         if cur+1 > max_ind:
#             return -1
#         x = max_ind
#         xv = max_ind + A[max_ind]
#         for j in range(cur+1, max_ind):
#             if j+A[j] > xv:
#                 x = j
#                 xv = j+A[j]

#         # print(x)
#         cur = x
#         minV += 1

#     return minV


# A = [0,3,1,0,4]
# A = [3,2,0,1,1,1,1]
# A = [100]*10**5
# A = [23, 19, 30, 6, 47, 0, 0, 0, 0, 49, 19, 25, 0, 10, 0, 46, 39, 5, 17, 35, 20, 0, 0, 38, 0, 32, 13, 32, 38, 4, 37, 0, 50, 9, 50, 4, 20, 47, 15, 41, 49, 16, 30, 13, 0, 6, 34, 50, 0, 4, 40, 0, 8, 21, 15, 32, 31, 0, 11, 0, 0, 0, 37, 29, 14, 44, 0, 32, 46, 0, 29, 0, 0, 48, 26, 20, 46, 14, 41, 11, 12, 0, 19, 42, 25, 0, 36, 0, 21, 43, 30, 0, 0, 0, 29, 27, 40, 43, 41, 49, 24, 42, 2, 11, 20, 17, 0, 26, 0, 44, 42, 0, 31, 34, 10, 41, 0, 0, 0, 41, 0, 0, 38, 18, 32, 5, 28, 14, 0, 18, 45, 37, 31, 38, 14, 2, 8, 26, 17, 16, 26, 0, 0, 1, 40, 50, 0, 17, 14, 0, 0, 35, 37, 0, 14, 39, 9, 0, 0, 14, 24, 49, 41, 1, 25, 40, 22, 30, 30, 33, 47, 4, 17, 12, 1, 15, 26, 0, 9, 34, 0, 42, 20, 0, 26, 45, 19, 0, 14, 15, 33, 0, 0, 34, 23, 3, 40, 0, 0, 26, 11, 21, 48, 0, 0, 7, 0, 16, 15, 0, 47, 0, 0, 15, 3, 45, 42, 0, 16, 3, 7, 15, 0, 5, 47, 30, 13, 13, 34, 22, 25, 48, 2, 24, 44, 36, 32, 46, 39, 11, 47, 0, 7, 10, 29, 8, 23, 3, 34, 34, 38, 43, 28, 33, 11, 0, 9, 4, 27, 36, 33, 23, 0, 16, 40, 0, 0, 5, 0, 40, 12, 33, 12, 0, 0, 0, 10, 0, 35, 25, 0, 0, 4, 2, 0, 4, 46, 12, 0, 28, 31, 15, 21, 1, 0, 0, 18, 0, 30, 4, 0, 44, 38, 35, 0, 25, 12, 9, 35, 22, 2, 42, 17, 0, 18, 43, 29, 38, 4, 30, 0, 10, 0, 40, 36, 0, 16, 50, 0, 48, 46, 0, 0, 17, 16, 32, 18, 28, 46, 36, 0, 11, 0, 32, 28, 9, 9, 31, 12, 36, 28, 18, 35, 49, 0, 0, 15, 36, 17, 18, 21, 15, 0, 20, 44, 0, 35, 34, 26, 10, 0, 1, 0, 20, 17, 50, 40, 0, 3, 20, 49, 0, 12, 26, 0, 0, 11, 8, 33, 0, 40, 0, 0, 4, 32, 48, 4, 0, 18, 5, 21, 19, 0, 9, 25, 0, 43, 35, 3, 4, 0, 20, 0, 43, 4, 13, 44, 0, 20, 12, 26, 48, 17, 5, 47, 0, 3, 40, 6, 26, 46, 35, 30, 8, 47, 42, 0, 43, 0, 38, 48, 0, 6, 31, 0, 12, 0, 44, 35, 0, 20, 0, 23, 0, 49, 1, 6, 9, 40, 5, 29, 3, 3, 0, 28, 20, 2, 0, 0, 42, 48, 0, 0, 0, 0, 0, 29, 47, 3, 7, 8, 0, 20, 16, 14, 42, 0, 42, 2, 15, 23, 0, 13, 41, 0, 0, 45, 8, 13, 0, 2, 0, 41, 0, 0, 17, 23, 0, 38, 7, 21, 44, 3, 16, 49, 26, 16, 29, 9, 27, 17, 0, 48, 21, 19, 0, 48, 33, 49, 26, 20, 38, 4, 0, 0, 48, 0, 49, 45, 32, 23, 46, 11, 29, 28, 46, 0, 0, 32, 40, 17, 44, 38, 0, 0, 0, 33, 25, 0, 40, 48, 33, 0, 10, 34, 23, 0, 9, 21, 39, 0, 50, 0, 2, 33, 17, 7, 46, 20, 0, 6, 34, 41, 29, 0, 44, 41, 34, 49, 17, 44, 9, 39, 3, 45, 32, 5, 18, 20, 46, 30, 0, 32, 40, 24, 50, 0, 43, 0, 27, 35, 2, 40, 0, 13, 0, 10, 0, 39, 15, 28, 15, 44, 28, 0, 28, 25, 0, 17, 29, 12, 11, 6, 50, 41, 0, 22, 0, 38, 7, 42, 0, 15, 44, 48, 17, 41, 12, 5, 0, 43, 0, 17, 49, 0, 48 ]
# print(solve1(A))

def search_on_left(v, arr):
    l = 0
    r = len(arr)-1
    while True:
        if l > r:
            return -1
        mid = (l+r)//2
        if mid == len(arr)-1:
            if v > arr[mid]:
                return mid
            return -1
        if v > arr[mid] and v <= arr[mid+1]:
            return mid
        elif v > arr[mid+1]:
            l = mid+1
        else:
            r = mid-1 
    return -1
def search_on_right(v, arr):
    l = 0
    r = len(arr)-1
    while True:
        if l > r:
            return -1
        mid = (l+r)//2
        if mid == len(arr)-1:
            if v >= arr[mid]:
                return mid
            return -1
        if v >= arr[mid] and v < arr[mid+1]:
            return mid
        elif v >= arr[mid+1]:
            l = mid+1
        else:
            r = mid-1 
    return -1


def find_on_left(finding_ind, nums1, nums2):
    l = 0
    r = len(nums1)-1
    while True:
        if l > r:
            return -1
        mid = (l+r)//2
        ind1 = search_on_left(nums1[mid], nums2)
        x = 0
        if ind1 != -1:
            x = mid+ind1+1
        else:
            x = mid
        if x == finding_ind:
            return mid
        if x > finding_ind:
            r = mid-1
        else:
            l = mid+1
    return -1

def find_on_right(finding_ind, nums1, nums2):
    l = 0
    r = len(nums1)-1
    while True:
        if l > r:
            return -1
        mid = (l+r)//2
        ind1 = search_on_right(nums1[mid], nums2)
        x = 0
        if ind1 != -1:
            x = mid+ind1+1
        else:
            x = mid
        if x == finding_ind:
            return mid
        if x > finding_ind:
            r = mid-1
        else:
            l = mid+1
    return -1

def solve4(nums1, nums2):
    n = len(nums1)+len(nums2)
    mid1 = -1
    mid2 = -1
    total = 0
    n_count = 0
    if n%2 == 0:
        mid1 = n//2-1
        mid2 = n//2
    else:
        mid1 = n//2
    # print('mid1', mid1, 'mid2', mid2)

    a1 = find_on_left(mid1, nums1, nums2)
    a2 = find_on_right(mid1, nums1, nums2)
    # print(a1, a2)
    if a1 != -1 or a2 != -1:
        total += nums1[max(a1, a2)]
        n_count += 1
    else:
        a1 = find_on_left(mid1, nums2, nums1)
        a2 = find_on_right(mid1, nums2, nums1)
        total += nums2[max(a1, a2)]
        n_count += 1
    if mid2 != -1:
        a1 = find_on_left(mid2, nums1, nums2)
        a2 = find_on_right(mid2, nums1, nums2)
        if a1 != -1 or a2 != -1:
            total += nums1[max(a1, a2)]
            n_count += 1
        else:
            a1 = find_on_left(mid2, nums2, nums1)
            a2 = find_on_right(mid2, nums2, nums1)
            total += nums2[max(a1, a2)]
            n_count += 1
    return float(total/n_count)

    




# nums1 = [1,1,3,3]
# nums2 = [1,1,3,3]

# nums1 = [1,1,1,1,1,1,1,1,1,1,4,4]
# nums2 = [1,3,4,4,4,4,4,4,4,4,4]


nums1 = [1]
nums2 = [1,2]

nums3 = nums1 + nums2
nums3 = sorted(nums3)
print(nums3, 'len', len(nums3))
if len(nums3)%2 == 0:
    mid1 = len(nums3)//2-1
    mid2 = len(nums3)//2
    print(float(nums3[mid1] + nums3[mid2])/2.0)
else:
    mid1 = len(nums3)//2
    print(float(nums3[mid1]))
print('----------')

# 1 1 1 1 3 3 3 3
# print(search(1, nums1))
print(solve4(nums1, nums2))



