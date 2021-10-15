"""
dizert: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('dizert_input.txt')


dx = [ 1, 1, -1, -1,]
dy = [ 1, -1, -1, 1,]

#현재, 지나온 상점수, 
def dfs(nowx, nowy, steps, move, startx, starty):
    global visited, result
    
    if move >= 4:
        return

    if nowx == startx and nowy == starty :
        if result < steps:
            result = steps
        return

    
    if 0 <= nowx < N and 0 <= nowy < N:
        
        if visited[MAP[nowx][nowy]] == 0:
            visited[MAP[nowx][nowy]] = 1
            
            dfs(nowx + dx[move], nowy + dy[move], steps + 1, move, startx, starty)

            dfs(nowx + dx[(move+1)%4], nowy + dy[(move+1)%4], steps + 1, move + 1, startx, starty)
            visited[MAP[nowx][nowy]] = 0
        else:
            return
    else:
        return
    
   

T = int(input())

for tc in range(1, T + 1):
    N =int(input())
    MAP = [list(map(int, input().rstrip().split())) for _ in range(N)]
    visited = [0] * 101
    result = -1
    for x in range(N-2):
        for y in range(1, N-1):
            visited[MAP[x][y]] = 1
            dfs(x+1,y+1,1,0,x,y)
            visited[MAP[x][y]] = 0
    
    print(f'#{tc} {result}')