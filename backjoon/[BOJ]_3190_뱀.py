import sys
from collections import deque

dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

N = int(sys.stdin.readline().rstrip())
MAP = [[0] * N for _ in range(N)]
K = int(sys.stdin.readline().rstrip())
for _ in range(K):
    xy = list(map(int, sys.stdin.readline().rstrip().split()))
    MAP[xy[0]-1][xy[1]-1] = 2

L = int(sys.stdin.readline().rstrip())

turn = [sys.stdin.readline().rstrip().split() for _ in range(L)]

stance = 0
live = True
L_idx = 0
nowx = 0
nowy = 0
time = 0
q = deque()
q.append([0,0])
MAP[0][0] = 1
while live:

    if len(turn) > L_idx and int(turn[L_idx][0]) == time:
        
        if turn[L_idx][1] == 'D':
            stance = (stance + 1) % 4
        elif turn[L_idx][1] == 'L':
            stance = stance - 1
            if stance == -1:
                stance = 3
        L_idx += 1

    nx = nowx + dx[stance]
    ny = nowy + dy[stance]
    if 0 <= nx < N and 0 <= ny < N:
        
        if MAP[nx][ny] == 0:
            MAP[nx][ny] = 1
            q.append([nx, ny])
            tmp = q.popleft()
            MAP[tmp[0]][tmp[1]] = 0
            nowx = nx
            nowy = ny
        elif MAP[nx][ny] == 2:
            MAP[nx][ny] = 1
            q.append([nx, ny])
            nowx = nx
            nowy = ny
        elif MAP[nx][ny] == 1:
            live = False
            break
    else:
        live = False
        break
    time += 1

print(time+1)