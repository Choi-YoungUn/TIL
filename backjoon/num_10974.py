import sys

N = int(sys.stdin.readline().strip())

temp = [0] * (N + 1)
vi = [0] * (N + 1)


def check(n, k):
    if  k == n+1:
        tmp = ''
        for t in temp[1:]:
            tmp += str(t) + ' '
        
        print(tmp.strip())
        return
    else:
        for x in range(1, n+1):
            if vi[x] == 0:
                temp[k] = x
                vi[x] = 1
                check(n, k+1)
                vi[x] = 0

check(N, 1)


# #모든 순열
# import sys

# N = int(sys.stdin.readline())
# arr = [-1] * N
# check = [0] * (N + 1)
# def dfs(k):
#     # 이번에 k번째 수를 고르겠다.
#     if k == N:
#         for i in range(N):
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