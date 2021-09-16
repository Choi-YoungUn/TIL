import sys
from collections import deque

M, N = map(int, sys.stdin.readline().split())
box = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]
st_x = 0
st_y = 0
Q = deque()
visited = [ [0] * M for _ in range(N) ]
for x in range(N):
    for y in range(M):
        if box[x][y] == 1:
            st_x = x
            st_y = y
            Q.append([st_x, st_y])
            visited[st_x][st_y] = 1
        elif box[x][y] == -1:
            visited[x][y] = -1

dr = [-1,1,0,0]
dc = [0,0,-1,1]

while len(Q) > 0:
    nowx = Q[0][0]
    nowy = Q[0][1]
    for x in range(4):
        next_i = nowx + dr[x]
        next_j = nowy + dc[x]
        if 0 <= next_i < N and 0 <= next_j < M:
            if box[next_i][next_j] == 0 and visited[next_i][next_j] == 0:
                Q.append([next_i, next_j])
                visited[next_i][next_j] = visited[nowx][nowy] + 1
    Q.popleft()
result = -1
for x in range(N):
    if 0 in visited[x]:
        result = -1
        break
    else:
        if result < max(visited[x]):
            result = max(visited[x]) - 1
print(result)