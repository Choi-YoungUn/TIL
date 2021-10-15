"""
claim: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('claim_input.txt')


def dfs(nowx, nowy, step, deep):
    global maxx, K
    di = [-1, 1, 0, 0]
    dj = [0, 0, -1, 1]
    
    if maxx < step:
        maxx = step
    visited[nowx][nowy] = 1
    for x in range(4):
        next_i = nowx + di[x]
        next_j = nowy + dj[x]
        if 0 <= next_i < N and 0 <= next_j < N:
            if visited[next_i][next_j] == 0:
                if MAP[next_i][next_j] < MAP[nowx][nowy]:
                    dfs(next_i, next_j, step+1, deep)
                elif deep == 1 and MAP[next_i][next_j] - K < MAP[nowx][nowy]:
                    temp = MAP[next_i][next_j]
                    MAP[next_i][next_j] = MAP[nowx][nowy] -1
                    dfs(next_i, next_j, step+1, 0)
                    MAP[next_i][next_j] = temp
    visited[nowx][nowy] = 0


T = int(input().strip())
for tc in range(1, T + 1):
    N, K = map(int, input().split())
    MAP = [list(map(int, input().split()))for _ in range(N)]
    Q = []
    maxx = 0
    for x in range(N):
        for y in range(N):
            if maxx < MAP[x][y]:
                maxx = MAP[x][y]
                Q.clear()
                Q.append([x,y])
            elif maxx == MAP[x][y]:
                Q.append([x,y])
    maxx = 0
    visited = [[0] * N for _ in range(N)]
    for x in Q:
        dfs(x[0], x[1], 1, 1)
        
    print("#{} {}".format(tc, maxx))