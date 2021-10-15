"""
004_pari: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('004_pari_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    nm = list(map(int,input().split()))
    temp = []
    for x in range(nm[0]):
        temp.append(list(map(int,input().split())))
    
    kill = 0
    for x in range(nm[0] - nm[1]+1):
        for y in range(nm[0] - nm[1]+1):
            temp_kill = 0
            for i in range(x, x + nm[1]):
                for j in range(y, y + nm[1]):
                    temp_kill += temp[i][j]
            if temp_kill > kill:
                kill = temp_kill

    print("#{} {}".format(test_case, kill))

# T = int(input())
# for tc in range(T):
#     N, M = map(int, input().split())
#     MAP = [[0 for _ in range(N + 1)]]
#     for i in range(N):
#         MAP += [[0] + list(map(int, input().split()))]
#     dp = [ [0] * (N + 1) for _ in range(N + 1) ]

#     for row in range(1, N + 1):
#         for col in range(1, N + 1):
#             dp[row][col] = dp[row - 1][col] + dp[row][col - 1] - dp[row - 1][col - 1] + MAP[row][col]
    
#     ans = 0
#     for row in range(M, N + 1):
#         for col in range(M, N + 1):
#             sum = dp[row][col] - dp[row - M][col] - dp[row][col - M] + dp[row - M][col - M]
#             if ans < sum:
#                 ans = sum
    
#     print("#{} {}".format(tc + 1, ans))