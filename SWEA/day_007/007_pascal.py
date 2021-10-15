"""
pascal: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('007_pascal_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    num = int(input())
    temp = []
    now_temp = []

    for x in range(1,num + 1):
        counts = 1
        for y in range(x):
            if x >= 2:
                if y == 0:
                    now_temp.append(1)
                elif y == x-1:
                    now_temp.append(1)
                else:
                    now_temp.append(temp[x - 2][y -1] + temp[x - 2][y])
            else:
                now_temp.append(y+ 1)
                
        temp.append(now_temp)
        now_temp = []


    print('#{}'.format(test_case))
    for x in range(num):
        result = ''
        for y in range(x + 1):
            result += str(temp[x][y]) + ' '
        print(result.strip())

# dp = [[0]*1000 for _ in range(100)]

# # 주의 사항 : 맨 처음 <- 직접 세팅

# dp[0][0] = 1

# for row in range(1,100):
#     for col in range(100):
#         dp[row][col] = dp[row-1][col] + dp[row - 1][col - 1]

# T = int(input())

# for tc in range(T):
#     N = int(input())
#     print("#{}".format(tc + 1))
#     for row in range(N):
#         for col in range(row + 1):
#             print("{} ".format(dp[row][col]), end = "")
#         print("")