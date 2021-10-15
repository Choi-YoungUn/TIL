"""
lis_sum: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('lis_sum_input.txt')

T = int(input().strip())

def dfs(now_x, now_y):
    di = [-1, 1, 0, 0] 
    dj = [0, 0, -1, 1]
    if now_x == N-1 and now_y == N-1 :
        return

    for add in range(4):
        next_x = now_x + di[add]
        next_y = now_y + dj[add]
        if 0 <= next_x < N and 0 <= next_y < N:
            tmp = visited[now_x][now_y] + MAP[next_x][next_y]
            if tmp < visited[next_x][next_y]:
                visited[next_x][next_y] = tmp
                dfs(next_x,next_y)


for tc in range(1, T + 1):
    N = int(input().strip())
    MAP = [list(map(int,input().split()))for _ in range(N)]
    visited = [[float('inf')]* N for _ in range(N)]
    visited[0][0] = MAP[0][0]
    dfs(0,0)
    print('#{} {}'.format(tc, visited[N-1][N-1]))


# # dp를 추가해서 속도를 높일 수 있다.

# def dfs(row, col):
#     global ans
#     if row == n-1 and col == n-1:
#         return MAP[row][col]# 오른쪽 아래(끝)이면 멈춤

#     if DP[row][col] != -1:
#         return DP[row][col]
#     ret = 2134567890
#     dr = [1,0]
#     dc = [0,1]
#     for i in range(2):
#         next_row = row + dr[i]
#         next_col = col + dc[i]
#         if not ( 0 <= next_row < n and 0 <= next_col < n):
#             continue # 맵을 벗어나면 무시
#         ret = min(ret, dfs(next_row, next_col) + MAP[row][col])
#         # row, col에서 n-1,n-1까지 갈 때의 비용
#     DP[row][col] = ret
#     return ret


# t = int(input())
# for tc in range(t):
#     n = int(input())
#     MAP = [ list(map(int, input().split())) for _ in range(n)]
#     DP = [[-1] * (n) for _ in range(n)]
#     print(dfs(0,0))
#     for dp in DP:
#         print(dp)