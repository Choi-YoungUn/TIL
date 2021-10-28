import sys


dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

def dfs(nowx,nowy, move, parsent):
    global total
    
    if move == CNT:
        total += parsent
        return

    for add in range(4):
        if can_move[add] == 0:
            continue

        nx = nowx + dx[add]
        ny = nowy + dy[add]
        if MAP[nx][ny] == 0:
            MAP[nx][ny] = 1
            dfs(nx, ny, move + 1, parsent * float(can_move[add]) * 0.01)
            MAP[nx][ny] = 0
        
CNT, E, W, S, N = map(int, sys.stdin.readline().split())
can_move = [N, S, W, E]
total = 0.0

MAP = [[0]* (CNT * 2 + 1)for _ in range(CNT * 2 + 1)]
startX, startY = CNT, CNT
MAP[CNT][CNT] = 1

dfs(startX, startY, 0, 1)
print(total)