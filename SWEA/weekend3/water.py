"""
water: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('water_input.txt')

from collections import deque

T = int(input().strip())
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    MAP = [input() for _ in range(N)]
    Q = deque()
    visited = [[-1] * M for _ in range(N)]
    for x in range(N):
        for y in range(M):
            if MAP[x][y] == 'W':
                visited[x][y] = 0
                Q.append([x, y])
    
    
    while len(Q) > 0:
        di = [-1, 1, 0, 0]
        dj = [0, 0, -1, 1]
        nowx, nowy = Q.popleft()
        
        for i in range(4):
            nx = nowx + di[i]
            ny = nowy + dj[i]
            if 0 <= nx < N and 0 <= ny < M:
                if visited[nx][ny] == -1:
                    visited[nx][ny] = visited[nowx][nowy] + 1
                    Q.append((nx, ny))
    
    cnt = 0
    for i in visited:
        for j in i:
            cnt += j

    print("#{} {}".format(tc, cnt))



    