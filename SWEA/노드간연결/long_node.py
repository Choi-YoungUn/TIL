"""
long_node: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('long_node_input.txt')


def dfs(now, cnt):
    global result
    if result < cnt:
        result = cnt
    for next in range(1, N+1):
        if visited[next] == 0:
            if MAP[now][next] == 1:
                visited[next] = 1
                dfs(next, cnt+1)
                visited[next] = 0


T = int(input())
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    MAP = [[0] * (N + 1) for _ in range(N + 1)]
    visited = [0] * (N+1)
    result = 0

    for _ in range(M):
        x, y = map(int, input().split())
        MAP[x][y] = 1
        MAP[y][x] = 1
    
    for x in range(1, N+1):
        visited[x] = 1
        dfs(x, 1)
        visited[x] = 0

    print(f'#{tc} {result}')