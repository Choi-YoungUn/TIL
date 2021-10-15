"""
008_N_Castle: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('008_N_Castle_input.txt', 'rt', encoding= 'UTF-8')

def check(num, start = 0):
    global counts, result, stack
    if start == num:
        counts += 1
    else:
        for x in range(num):
            
            if x not in stack:
                result[start] = x
                stack.append(x)
                check(num, start + 1)
                stack.pop(-1)

for tc in range(10):
    N = int(input())
    stack = []
    result = [-1] * N
    counts = 0
    check(N)
    print("#{} {}".format(tc + 1, counts))

# N = 8

# path = [-1] * N

# col = [0] * N

# def dfs(row):
#     if row == N:
#         return
#     for i in range(N):
#         path[row] = i
#         if col[i] == 1:
#             continue # i번에 두고 싶은데 이미 사용중이면 넘어가라

#         col[i] = 1 # i번 col에 두겠다.
#         dfs(row + 1)
#         col[i] = 0 # i번 col에 두는 작업 끝이 나서 원상복구

#         path[row] = -1

# dfs(0)