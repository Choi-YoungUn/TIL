"""
007_paper: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('007_paper_input.txt')

def make(num):
    if not num:
        return 0
    dp = [0] * (num)

    if dp[num-1] == 0:
        if num == 1:
            dp[num-1] = 1
        elif num == 2:
            dp[num-1] = 3
        else:
            dp[num-1] = make(num - 1) + 2 * make(num - 2)
    return dp[num-1]

T = int(input())
for test_case in range(1, T + 1):
    n = int(input())
    print("#{} {}".format(test_case, make(n // 10)))


# dp = [0] * 301

# dp[1] = 1
# dp[2] = 3

# for col in range(3, 301):
#     dp[col] = dp[col - 1] + 2 * dp[col - 2]

# T = int(input())
# for tc in range(T):
#     N = int(input())
#     print("#{} {}".format(tc + 1, dp[N // 10]))