# Given A, B, C, find whether C is formed by the interleaving of A and B.
# Input Format:*
# The first argument of input contains a string, A.
# The second argument of input contains a string, B.
# The third argument of input contains a string, C.
# A: cabde
# B: cfg
# C: cabcdfge
        
# Output Format:
# Return an integer, 0 or 1:
# => 0 : False
# => 1 : True
# Constraints:
# 1 <= length(A), length(B), length(C) <= 150


# len_c = len_a + len_b
# c_can_be_formed[i] = 1 -->  c_can_be_formed[n] 

# i = 2 cab
# i = len_c-1 return c_can_be_formed[i]

# len_c = len(c)
# dp = [0 for i in range(len_c)]
# dp[i] = answer for the question: can I form substring of C up to i
# final answer is dp[len_c-1]


# A: cabde
# B: cfg
# C: cabcdfge

def solve(A,B,C):
    len_c = len(C)
    dp = [0 for _ in range(len_c)]
    if C[0] == A[0] or C[0] == B[0]:
        dp[0] = 1
    for i in range(1, len_c):
        for j in range(min(i+1, len(A))):
            k = i-j-1
            print(j,k,i)
            if dp[i] == 1: continue
            if k < 0:
                if A[:j+1] == C[:i+1]:
                    dp[i] = 1
                else:
                    dp[i] = 0
                continue
            if k >= len(B): continue
            if dp[i-1] == 1 and (A[j] == C[i] or B[k] == C[i]):
                dp[i] = 1
            else:
                dp[i] = 0
    print(dp)
    return dp[len_c-1]

print(solve('cabde', 'cfg', 'cabcdfge'))
# print(solve('abc', 'abc', 'aacbbc'))

# aavaa
# bbccaa

# aabbccvaaa
