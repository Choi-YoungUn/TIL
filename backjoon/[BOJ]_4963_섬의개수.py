import sys
sys.setrecursionlimit(100000)

dx = [-1, 1, 0, 0, 1, 1, -1, -1]
dy = [0, 0, -1, 1, 1, -1, -1, 1]
def dfs(nowx, nowy):

    for x in range(8):
        nx = nowx + dx[x]
        ny = nowy + dy[x]
        if 0 <= nx < H and 0 <= ny < W:
            if visited[nx][ny] == 0:
                if MAP[nx][ny] == 1:
                    visited[nx][ny] = 1
                    dfs(nx, ny)

while True:
    W, H = map(int, sys.stdin.readline().split())
    if W == 0 and H == 0:
        break
    MAP = [list(map(int, sys.stdin.readline().split()))for _ in range(H)]
    visited = [[0] * W for _ in range(H)]
    result = 0
    for x in range(H):
        for y in range(W):
            if visited[x][y] == 0 and MAP[x][y] == 1:
                visited[x][y] = 1
                result += 1
                dfs(x, y)

    print(result)

