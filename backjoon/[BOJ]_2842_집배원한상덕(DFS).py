import sys
sys.setrecursionlimit(100000)
# 상 하 좌 우  남동  남서  북서 북동
dx = [-1, 1, 0, 0, 1, 1, -1, -1]
dy = [0, 0, -1, 1, 1, -1, -1, 1]


def find_p():
    re_x, re_y = 0, 0
    house = 0
    for x in range(N):
        for y in range(N):
            if MAP[x][y] == 'P':
                re_x = x
                re_y = y
            elif MAP[x][y] == 'K':
                house += 1

    return (re_x, re_y, house)


def dfs(nowx, nowy, K, min, max):
    global end_kx, end_ky, gap

    now_k = K
    minner = min
    maxxer = max
    if HILL[nowx][nowy] > maxxer:
        maxxer = HILL[nowx][nowy]
        
    if HILL[nowx][nowy] < minner:
        minner = HILL[nowx][nowy]

    now_gap = maxxer - minner

    if now_gap >= gap:
        return

    if MAP[nowx][nowy] == 'K':
        now_k += 1

    if now_k == K_cnt:
        end_kx = nowx
        end_ky = nowy
        gap = now_gap
        return

    for add in range(8):
        nx = nowx + dx[add]
        ny = nowy + dy[add]
        if 0 <= nx < N and 0 <= ny < N:
            if Find_k_map[nx][ny] == 0:
                Find_k_map[nx][ny] = 1
                
                dfs(nx, ny, now_k, minner, maxxer)
                Find_k_map[nx][ny] = 0


N = int(sys.stdin.readline())
MAP = [sys.stdin.readline().rstrip() for _ in range(N)]
HILL = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]
Find_k_map = [[0] * N for _ in range(N)]

post = find_p()
start_x, start_y, K_cnt = post[0], post[1], post[2]
end_kx, end_ky = 0, 0
pp =HILL[start_x][start_y]
gap = float('inf')
Find_k_map[start_x][start_y] = 1
dfs(start_x, start_y, 0, pp, pp)

print(gap)