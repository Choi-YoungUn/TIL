import sys
sys.setrecursionlimit(10000)

dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]

def dfs(nowx, nowy):
    global tm_wolf, tm_sheep
    tmp = True
    for add in range(4):
        nx = nowx + dx[add]
        ny = nowy + dy[add]

        if 0 <= nx < NM[0] and 0 <= ny < NM[1]:
            if visited[nx][ny] == 0:

                if MAP[nx][ny] == '.':
                    visited[nx][ny] = 1
                    dfs(nx, ny)
                elif MAP[nx][ny] == 'v':
                    visited[nx][ny] = 1
                    tm_wolf += 1
                    dfs(nx, ny)
                elif MAP[nx][ny] == 'o':
                    visited[nx][ny] = 1
                    tm_sheep += 1
                    dfs(nx, ny)
        else:
            tmp = False
    return tmp


NM = list(map(int, sys.stdin.readline().rstrip().split()))
MAP = [sys.stdin.readline().rstrip() for _ in range(NM[0])]
visited = [[0] * NM[1] for _ in range(NM[0])]

tm_wolf = 0
tm_sheep = 0
result_wolf = 0
result_sheep = 0
for x in range(1, NM[0] - 1):
    for y in range(1, NM[1] - 1):
        if visited[x][y] == 0 :
            
            if MAP[x][y] == 'v':
                visited[x][y] = 1
                tm_sheep = 0
                tm_wolf = 1
                out = dfs(x, y)
                if out:
                    if tm_wolf >= tm_sheep:
                        result_wolf += tm_wolf
                    else:
                        result_sheep += tm_sheep
            elif MAP[x][y] == 'o':
                visited[x][y] = 1
                tm_sheep = 1
                tm_wolf = 0
                out = dfs(x, y)
                if out:
                    if tm_wolf >= tm_sheep:
                        result_wolf += tm_wolf
                    else:
                        result_sheep += tm_sheep
        
print(result_sheep, result_wolf)