def solution(A):
    N = len(A)
    sorted_from_left = []
    for i in range(0, N):
        if len(sorted_from_left) == 0:
            sorted_from_left.append(True)
        elif A[i] >= A[i-1] and sorted_from_left[-1] == True:
            sorted_from_left.append(True)
        else:
            sorted_from_left.append(False)
    sorted_from_right = []
    for i in range(N-1, -1, -1):
        if len(sorted_from_right) == 0:
            sorted_from_right.append(True)
        elif A[i] <= A[i+1] and sorted_from_right[-1] == True:
            sorted_from_right.append(True)
        else:
            sorted_from_right.append(False)
    sorted_from_right = sorted_from_right[::-1]
    # print(sorted_from_left)
    # print(sorted_from_right)

    c = 0
    for i in range(N):
        f1 = f2 = False
        if i == 0:
            f1 = True
            if i == N-1 or sorted_from_right[i+1] == True:
                f2 = True
        elif i == N-1:
            f2 = True
            if i == 0 or sorted_from_left[i-1] == True:
                f1 = True
        elif sorted_from_left[i-1] == True and sorted_from_right[i+1] == True and A[i-1] <= A[i+1]:
            f1 = True
            f2 = True
       
        if f1 == True and f2 == True:
            c += 1
    return c
#arr = [1 for i in range(1, 100001)]
#arr = [1,2,3,1,1,2,3]
#arr = [4,5,2,3,4]
arr = [1234]
print(solution(arr))