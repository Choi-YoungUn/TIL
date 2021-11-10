import sys
from collections import deque


N, M = map(int, sys.stdin.readline().rstrip().split())
MAP_in = [sys.stdin.readline().rstrip()for _ in range(N)]
TOP = 0
result = 0
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
for x in range(N):
    for y in range(M):
        TOP = max(TOP, int(MAP_in[x][y]))

MAP = [[[0] * M for _ in range(N)] for _ in range(TOP)]
for x in range(N):
    for y in range(M):
        for z in range(int(MAP_in[x][y])):
            MAP[z][x][y] = 1


for z in range(TOP):
    visited = [[0] * M for _ in range(N)]
    q = deque()
    
    for x in range(1,N-1):
        for y in range(1, M-1):
            cnt = 0
            if visited[x][y] == 0 and MAP[z][x][y] == 0:
                visited[x][y] = 1
                cnt += 1
                q.append((x, y))
            put = True

            dd = 1
            while len(q) > 0:
                now = q.popleft()
                nowx = now[0]
                nowy = now[1]
                for add in range(4):
                    nx = nowx + dx[add]
                    ny = nowy + dy[add]
                    if 0 > nx or N <= nx or  0 > ny or M <= ny:
                        put = False
                        continue
                    if visited[nx][ny] == 1 or MAP[z][nx][ny] == 1:
                        continue
                    cnt += 1
                    visited[nx][ny] = 1
                    q.append((nx,ny))
            if put:
                result += cnt

print(result)