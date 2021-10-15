"""
ele_cart: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('ele_cart_input.txt')

def dfs_root(now):
    global result
    if 0 not in  visited:
        lists = visited + [1]
        tmp = 0
        for move in range(len(lists)-1):
            tmp += MAP[lists[move]-1][lists[move+1]-1]
        if result > tmp:
            result = tmp
        return

    for next in range(N):
        if visited[next] == 0:
            visited[next] = visited[now]+1
            dfs_root(next)
            visited[next] = 0


T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input().strip())
    MAP = [list(map(int,input().split()))for _ in range(N)]
    visited = [0] * N
    visited[0] = 1
    result = float('inf')
    dfs_root(0)

    print('#{} {}'.format(tc, result))



################## 전자카트


# def dfs(now = 0, cnt = 1, sum = 0):
#     global ans
#     if cnt == n :
#         ans = min(ans, sum + MAP[now][0])
#         return
#     if sum >= ans:
#         return # 가지치기
#     for next in range(1, n):
#         if check[next]:
#             continue # 이미 갔던 점이면 무시
#         check[next] = True
#         dfs(next, cnt + 1, sum + MAP[now][next])
#         check[next] = False

# # 전에 했던 경로

# t = int(input())
# for tc in range(t):
#     n = int(input())
#     MAP = [ list(map(int, input().split())) for _ in range(n)]
#     # index : 0~n-1
#     # 본래 1~n번에서 1씩 빼서 사용
#     check = [False] * (n)
#     ans = 2134567890
#     dfs()
#     print(f"#{tc + 1} {ans}")