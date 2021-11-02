import sys

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
def dfs(nowx, nowy):
    global visited
    for a in range(4):
        nx = nowx + dx[a]
        ny = nowy + dy[a]
        if 0 <= nx < N and 0 <= ny < M:
            if visited[nx][ny] == 0:
                if MAP[nx][ny] == 1:
                    visited[nx][ny] = 1
                    dfs(nx,ny)


T = int(sys.stdin.readline())
for tc in range(1, T + 1):
    M, N, K = map(int, sys.stdin.readline().split())
    MAP = [[0] * M for _ in range(N)]
    visited = [[0] * M for _ in range(N)]
    for _ in range(K):
        x, y = map(int, sys.stdin.readline().split())
        MAP[y][x] = 1
    cnt = 0
    for x in range(N):
        for y in range(M):
            if visited[x][y] == 0 and MAP[x][y] == 1:
                cnt += 1
                dfs(x, y)

    print(cnt)