"""
010_miro_far: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('010_miro_far_input.txt')

from collections import deque

T = int(input())
for tc in range(T):
    N = int(input())
    MAP = [ list(map(int, input().rstrip())) for _ in range(N) ]
    visited = [ [0] * N for _ in range(N) ]
    Q = deque()
    endx = 0
    endy = 0
    for x in range(N):
        for y in range(N):
            if MAP[x][y] == 2:
                visited[x][y] = 1
                Q.append([x, y])
            elif MAP[x][y] == 3:
                endx = x
                endy = y
    dr = [-1,1,0,0]
    dc = [0,0,-1,1]

    while len(Q) > 0:
        nowx = Q[0][0]
        nowy = Q[0][1]
        for x in range(4):
            next_i = nowx + dr[x]
            next_j = nowy + dc[x]
            if 0 <= next_i < N and 0 <= next_j < N:
                if MAP[next_i][next_j] == 0 and visited[next_i][next_j] == 0:
                    Q.append([next_i, next_j])
                    visited[next_i][next_j] = visited[nowx][nowy] + 1
                if MAP[next_i][next_j] == 3:
                    visited[next_i][next_j] = visited[nowx][nowy] + 1
                    Q.clear()
        if len(Q) > 0:
            Q.popleft()
    if visited[endx][endy] == 0:
        print("#{} {}".format(tc, visited[endx][endy]))
    else:
        print("#{} {}".format(tc, visited[endx][endy] - 2))