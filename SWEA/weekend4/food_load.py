"""
food_load: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('food_load_input.txt')


from collections import deque
T = int(input())
for tc in range(1, T + 1):
    N = int(input())
    MAP = [input().strip() for _ in range(N)]
    cost_map = [[9999999] * N for _ in range(N)]

    q = deque()
    q.append((0,0))

    dx = [-1, 1, 0 ,0]
    dy = [0, 0, -1, 1]
    cost_map[0][0] = 0
    while q:
        now = q.popleft()
        now_x = now[0]
        now_y = now[1]
        for a in range(4):
            nx = now_x + dx[a]
            ny = now_y + dy[a]
            if 0 <= nx < N and 0 <= ny < N :
                cost = int(MAP[nx][ny])
                if cost_map[nx][ny] > cost_map[now_x][now_y] + cost:
                    cost_map[nx][ny] = cost_map[now_x][now_y] + cost
                    q.append((nx, ny))
    print(f'#{tc} {cost_map[N-1][N-1]}')