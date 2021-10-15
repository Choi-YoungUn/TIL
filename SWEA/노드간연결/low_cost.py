"""
low_cost: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('low_cost_input.txt')


from collections import deque
T = int(input())
for tc in range(1, T +1):
    N = int(input())
    MAP = [list(map(int, input().split()))for _ in range(N)]
    inf = float('inf')
    gus_map = [[inf]* N  for _ in range(N)]
    gus_map[0][0] = 0
    q = deque()
    q.append((0,0))
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]
    while q:
        now = q.popleft()
        now_x = now[0]
        now_y = now[1]
        for a in range(4):
            nx = now_x + dx[a]
            ny = now_y + dy[a]
            if 0 <= nx < N and 0 <= ny < N:
                gus = 1
                if MAP[nx][ny] > MAP[now_x][now_y]:
                    gus += (MAP[nx][ny] - MAP[now_x][now_y])
                    
                if gus_map[nx][ny] > gus_map[now_x][now_y] + gus:
                    gus_map[nx][ny] = gus_map[now_x][now_y] + gus
                    q.append((nx,ny))
    print(f'#{tc} {gus_map[N-1][N-1]}')
