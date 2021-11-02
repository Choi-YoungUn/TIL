import sys
sys.setrecursionlimit(100000)
dx = [0, 1]
dy = [1, 0]
def dfs(nowx, nowy):
    global result
    if result == 'HaruHaru':
        return

    if MAP[nowx][nowy] == -1:
        result = 'HaruHaru'
        return 

    for x in range(2):
        nx = nowx + dx[x] * MAP[nowx][nowy]
        ny = nowy + dy[x] * MAP[nowx][nowy]
        if 0 <= nx < N and 0 <= ny < N:
            if visited[nx][ny] == 0:
                visited[nx][ny] = 1
                dfs(nx,ny)
                


N = int(sys.stdin.readline())
MAP = [list(map(int, sys.stdin.readline().split()))for _ in range(N)]
visited = [[0] * N for _ in range (N)]
result = 'Hing'
visited[0][0] = 1
dfs(0,0)
print(result)