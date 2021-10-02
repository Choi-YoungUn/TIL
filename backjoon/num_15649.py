import sys

# # N과 M(1)
# import sys

# N, M = map(int, sys.stdin.readline().split())
# arr = [-1] * N
# check = [0] * (N + 1)
# def dfs(k):
#     # 이번에 k번째 수를 고르겠다.
#     if k == M:
#         for i in range(M):
#             print(arr[i], end = " ")
#         print("")
#         return
#     for i in range(1, N + 1):
#         if check[i] == 1: continue # 이미 골랐던 수
#         arr[k] = i
#         check[i] = 1
#         dfs(k + 1)
#         check[i] = 0

# dfs(0)
#모든 순열
import sys

N, M = map(int, sys.stdin.readline().split())
arr = [-1] * M
check = [0] * (N + 1)
def dfs(k):
    # 이번에 k번째 수를 고르겠다.
    if k == M:
        for i in range(M):
            print(arr[i], end = " ")
        print("")
        return
    for i in range(1, N + 1):
        if check[i] == 1: continue # 이미 골랐던 수
        arr[k] = i
        check[i] = 1
        dfs(k + 1)
        check[i] = 0

dfs(0)